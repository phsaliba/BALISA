#include "VariableHandler.hpp"


map<string, double> create_trasported_var_map(vector<string> input_transported_vars) {
	map<string, double> transported_vars;
	for (string transported_var : input_transported_vars) {
		transported_vars.insert({ transported_var, 0. });
	}
	return transported_vars;
}