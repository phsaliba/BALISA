#pragma once
#include<iostream>

#include "Cell1D.hpp"

Cell1D::Cell1D(int input_cell_id, Node1D* input_west_node, Node1D* input_east_node)
    : west_node(input_west_node),
    east_node(input_east_node)
{
    cell_id = input_cell_id;

    x = get_average(input_east_node->get_x(), input_west_node->get_x());
    area = get_average(input_east_node->get_area(), input_west_node->get_area());
    dx = input_east_node->get_x() - input_west_node->get_x();

    u = 0.;
    v = 0.;
    w = 0.;
}

int Cell1D::get_id() {
    return cell_id;
}

double Cell1D::get_x() {
    return x;
}

double Cell1D::get_dx() {
    return dx;
}

double Cell1D::get_area() {
    return area;
};

void Cell1D::display_cell_data() {
    printf("\n=======================\n");
    printf("cell %d:\t", cell_id);
    printf("x: %.2f\t", x);
    printf("A: %.2f\t", area);
    return;
};