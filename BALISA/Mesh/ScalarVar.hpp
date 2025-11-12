#include <string>

using std::string;

class ScalarVar {
public:
    float value;
    ScalarVar(string input_var_name, float input_value);
    string get_name();
private:
    string var_name;
};
