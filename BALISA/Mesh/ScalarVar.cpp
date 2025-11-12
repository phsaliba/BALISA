#include "ScalarVar.hpp"

ScalarVar::ScalarVar(string input_var_name, float input_value){
	value = input_value;
	var_name = input_var_name;
}

string ScalarVar::get_name() {
	return var_name;
}
