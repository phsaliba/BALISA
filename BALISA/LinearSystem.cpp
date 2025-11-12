#pragma once

#include <stdexcept>

#include "LinearSystem.hpp"
using std::invalid_argument;

LinearSystemSolver::LinearSystemSolver(MatrixXd input_square_matrix, VectorXd input_const_vector) {
	//This method assumes matrix is diagonally dominant,
	// should always be the case for finite-volume
	size = static_cast<int>(input_const_vector.size());
	int n_rows = static_cast<int>(input_square_matrix.rows());
	if (size != n_rows) throw invalid_argument("Input matrix and const_vector dimensions are not compatible");
	int n_columns = static_cast<int>(input_square_matrix.cols());
	if (size != n_columns) throw invalid_argument("Input matrix is not square");
	square_matrix = input_square_matrix;
	const_vector = input_const_vector;
}

VectorXd LinearSystemSolver::compute_single_jacobi_iteration(VectorXd *iteration_unknowns) {
	VectorXd next_iteration_unkowns = iteration_matrix * (*iteration_unknowns) + iteration_vector;
	return next_iteration_unkowns;
}

void LinearSystemSolver::compute_single_gauss_seidel_iteration(VectorXd* iteration_unknowns) {
	//for (int i = 0; i < size; i++) {
	//	(*iteration_unknowns)(i) = iteration_matrix.row(i) * (*iteration_unknowns) + iteration_vector(i);
	//}
	auto lower_matrix = square_matrix.triangularView<Eigen::Lower>();
	auto upper_matrix = square_matrix.triangularView<Eigen::StrictlyUpper>();

	VectorXd rhs = const_vector - upper_matrix * (*iteration_unknowns);
	(*iteration_unknowns) = lower_matrix.solve(rhs);
}

double LinearSystemSolver::compute_residuals(VectorXd* iteration_unknowns) {
	double ref_value = const_vector(0);
	VectorXd current_product_vector = (square_matrix * (*iteration_unknowns) - const_vector) / ref_value;
	return current_product_vector.cwiseAbs().maxCoeff();
}

VectorXd LinearSystemSolver::solve(int iter_limit, double target_residual, double init_value, string method) {
	VectorXd unknowns_vector = VectorXd::Constant(size, init_value);
	bool converged = false;
	if (method == "jacobi") {
		init_iteration_vector();
		init_iteration_matrix();
	}
	for (int iteration = 0; iteration < iter_limit && !converged; iteration++) {
		printf("Running iteration %d \r", iteration + 1);
		if (method == "jacobi") {
			unknowns_vector = compute_single_jacobi_iteration(&unknowns_vector);
		}
		else {
			compute_single_gauss_seidel_iteration(&unknowns_vector);
		}
		if ((iteration % 10) == 0) {
			converged = check_convergence(&unknowns_vector, target_residual);
		}
	}
	printf("\n\n");
	return unknowns_vector;
}

bool LinearSystemSolver::check_convergence(VectorXd *unknowns_vector, double target_residual) {
	double max_residual = compute_residuals(unknowns_vector);
	bool check = false;
	if (max_residual < target_residual) {
		check = true;
	}
	printf("\t\t\t\tMax residual is % lf\r", max_residual);
	return check;
}

void LinearSystemSolver::init_iteration_vector() {
	iteration_vector = VectorXd::Constant(size, 0.);
	for (int i = 0; i < size; i++) {
		iteration_vector(i) = const_vector(i) / square_matrix(i, i);
	}
}

void LinearSystemSolver::init_iteration_matrix(){
	iteration_matrix = MatrixXd::Constant(size, size, 0.);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i != j) {
				iteration_matrix(i, j) = -1. * square_matrix(i, j) / square_matrix(i, i);
			}
		}
	}
}

