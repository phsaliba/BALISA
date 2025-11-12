#pragma once

#include <math.h>
#include <Eigen/Dense>
#include <string>
#include <chrono>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::ArrayXd;
using std::string;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

class LinearSystemSolver {
public:
	LinearSystemSolver(MatrixXd input_square_matrix, VectorXd input_const_vector);
	VectorXd solve(int iter_limit, double target_residual, double init_value, string method);
	//VectorXd solve_gauss_seidel(int iter_limit, double target_residual);
private:
	int size;
	VectorXd const_vector;
	VectorXd iteration_vector;
	MatrixXd square_matrix;
	MatrixXd iteration_matrix;
	void init_iteration_vector();
	void init_iteration_matrix();
	VectorXd compute_single_jacobi_iteration(VectorXd *iteration_unknowns);
	void compute_single_gauss_seidel_iteration(VectorXd *iteration_unknowns);
	double compute_residuals(VectorXd *iteration_unknowns);
	bool check_convergence(VectorXd* unknowns_vector, double target_residual);
};