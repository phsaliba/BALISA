#pragma once
#include "SteadyDiffusion1D.hpp"
#include "VariableHandler.hpp"


SteadyDiffusion1D::SteadyDiffusion1D(Mesh1D* input_mesh) : mesh(*input_mesh) {}

void SteadyDiffusion1D::set_transport_equation(string var_name, double west_value, double east_value, double diffusion_coefficient) {
	mesh.west_bc.transported_vars.insert({var_name, west_value});
	mesh.east_bc.transported_vars.insert({var_name, east_value});

	transported_vars.push_back(var_name);
	diffusion_coefficients.insert({ var_name, diffusion_coefficient });
	for (int node_id = 0; node_id < mesh.get_mesh_size(); node_id++) {
		(mesh.get_node(node_id))->transported_vars.insert({var_name, 0.});
	}
}

double SteadyDiffusion1D::cell_gradient_coefficient(Node1D* left_node, Node1D* right_node, string var_name) {
	double area = get_average(left_node->get_area(), right_node->get_area());
	double dx = right_node->get_x() - left_node->get_x();

	return area * diffusion_coefficients[var_name] / dx;
}

tuple <MatrixXd, VectorXd> SteadyDiffusion1D::build_equation_matrices(string var_name) {
	int mesh_size = mesh.get_mesh_size();
	MatrixXd a_matrix = MatrixXd::Constant(mesh_size, mesh_size, 0.);
	VectorXd b_vector = VectorXd::Constant(mesh_size, 0.);
	double west_coef = 0., east_coef = 0.;
	for (int i = 0; i < mesh_size; i++) {
		double common_source_term = 0.;
		double u_source = 0.;
		Node1D* center_node = mesh.get_node(i);

		if (i > 0.) {
			west_coef = east_coef;
			a_matrix(i, i - 1) -= west_coef;
		}
		else {
			common_source_term = cell_gradient_coefficient(&mesh.west_bc, center_node, var_name);
			u_source = common_source_term * mesh.west_bc.transported_vars[var_name];
		}

		if (i < (mesh_size - 1)) {
			east_coef = cell_gradient_coefficient(center_node, mesh.get_node(i + 1), var_name);
			a_matrix(i, i + 1) -= east_coef;
		}
		else {
			east_coef = 0.;
			common_source_term = cell_gradient_coefficient(center_node, &mesh.east_bc, var_name);
			u_source = common_source_term * mesh.east_bc.transported_vars[var_name];
		}
		double p_source = -1. * common_source_term;
		a_matrix(i, i) = west_coef + east_coef - p_source;
		b_vector(i) = u_source;
	}

	return std::make_tuple(a_matrix, b_vector);
}

Mesh1D SteadyDiffusion1D::solve(string var_name, int iter_limit, double target_residual, double init_value, string method) {
	int mesh_size = mesh.get_mesh_size();

	tuple<MatrixXd, VectorXd> equation_tuple = build_equation_matrices(var_name);
	MatrixXd a_matrix = std::get<0>(equation_tuple);
	VectorXd b_vector = std::get<1>(equation_tuple);

	LinearSystemSolver diffusion_problem(a_matrix, b_vector);
	VectorXd solution_vector = diffusion_problem.solve(iter_limit, target_residual, init_value, method);

	for (int i = 0; i < mesh_size; i++) {
		mesh.get_node(i)->transported_vars[var_name] = solution_vector[i];
	}
	return mesh;
}

void SteadyDiffusion1D::display_solution() {
    int mesh_size = mesh.get_mesh_size();

    printf("Displaying node information:\n");
    for (int node_id = 0; node_id < mesh_size; node_id++) {
		Node1D node_to_print = *mesh.get_node(node_id);
		node_to_print.display_node_data();
		for (string var_name : transported_vars) {
			printf("%s = %.2lf", var_name.c_str(), node_to_print.transported_vars[var_name]);
		}
		printf(" vs %.2lf", 800. * node_to_print.get_x() + 100.);
    };
    printf("\n");
}
