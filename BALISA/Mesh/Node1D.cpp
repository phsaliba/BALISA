#pragma once
#include "Node1D.hpp"
Node1D::Node1D(int input_id, double input_x, double input_area){
    node_id = input_id;
    x = input_x;
    area = input_area;
}

void Node1D::display_node_data(){
    printf("\n=======================\n");
    printf("node %d:\t", node_id);
    printf("x = %.3f\t", x);
    printf("A =  %.3f\t", area);
}

int Node1D::get_id(){
    return node_id;
}

double Node1D::get_x(){
    return x;
}

double Node1D::get_area(){
    return area;
}

void write_node_to_csv(FILE* node_file, Node1D node_to_print) {
    fprintf(node_file, "%d, %f, %f\n", node_to_print.get_id(), node_to_print.get_x(), node_to_print.get_area());
}