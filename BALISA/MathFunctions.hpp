#pragma once

#include <vector>
using std::vector;

double get_average(double value1, double value2);

vector<int> get_matrix_dimmensions(vector<vector<double>> *matrix);

vector<double> matrix_vector_multiplication(vector<vector<double>> *left_matrix, vector<double> *right_vector);