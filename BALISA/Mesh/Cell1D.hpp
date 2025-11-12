#pragma once
#include "Node1D.hpp"
#include "../MathFunctions.hpp"

class Cell1D {
public:
    double u;
    double v;
    double w;

    Cell1D(int input_cell_id, Node1D *input_west_node, Node1D* input_east_node);

    int get_id();
    double get_x();
    double get_dx();
    double get_area();
    void display_cell_data();

    Node1D *west_node;
    Node1D *east_node;
private:
    int cell_id;
    double x;
    double dx;
    double area;
};