#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include "Mesh/mesh_builder.hpp"
#include <Eigen/Dense>
#include "LinearSystem.hpp"

using std::string;
using std::vector;
using std::tuple;
using std::map;
using Eigen::MatrixXd;
using Eigen::VectorXd;

class SteadyDiffusion1D {
	public:
		SteadyDiffusion1D(Mesh1D* input_mesh);

		void set_transport_equation(string var_name, double west_value, double east_value, double diffusion_coefficient);
		Mesh1D solve(string var_name, int iter_limit, double target_residual, double init_value = 0., string method = "gauss-seidel");

		void display_solution();


private:
		Mesh1D mesh;

		vector<string> transported_vars;
		map<string, double> diffusion_coefficients;

		double cell_gradient_coefficient(Node1D* left_node, Node1D* right_node, string var_name);
		tuple <MatrixXd, VectorXd> build_equation_matrices(string var_name);
		//Node1D *west_node;
		//Node1D *east_node;
		
		//Cell1D *west_cell;
		//Cell1D *east_cell;
};