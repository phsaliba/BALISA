#pragma once

#include <vector>
#include <stdexcept>

using std::vector;
using std::invalid_argument;

double get_average(double value1, double value2) {
	return (value1 + value2) / 2;
}

vector<int> get_matrix_dimmensions(vector<vector<double>> *matrix) {
	vector<int> dimensions = { static_cast<int>(matrix->size()), static_cast<int>(matrix->at(0).size()) };
	return dimensions;
}

vector<double> matrix_vector_multiplication(vector<vector<double>> *left_matrix, vector<double> *right_vector) {
	vector<int> left_dimensions = get_matrix_dimmensions(left_matrix);
	int right_size = right_vector->size();
	if (left_dimensions.at(1) != right_size) throw invalid_argument("Input matrix and const_vector dimensions are not compatible");
	int left_rows = left_dimensions.at(0);
	
	vector<double> output(left_rows);
	for (int i = 0; i < left_rows; i++) {
		for (int j = 0; j < right_size; j++) {
			output[i] += left_matrix->at(i).at(j) * right_vector->at(j);
		}
	}
	return output;
}
