#include<iostream>
#include<stdio.h> 

#include<vector>
#include<string>

using std::string;
using std::vector;

#include "Mesh1D.hpp"
#include "mesh_file_helper.hpp"

Mesh1D::Mesh1D(std::vector<Node1D> input_node_vector, double input_west_area, double input_east_area, double input_west_x, double input_east_x) :
west_bc(-1, input_west_x, input_west_area),
east_bc(-1, input_east_x, input_east_area)
{
    node_vector = input_node_vector;

    for (int cell_id = 0; cell_id < node_vector.size() - 1; cell_id++) {
        Cell1D new_cell(cell_id, &node_vector.at(cell_id), &node_vector.at(cell_id + 1));
        cell_vector.push_back(new_cell);
    }

    west_area = input_west_area;
    east_area = input_east_area;
    
    west_x = input_west_x;
    east_x = input_east_x;
}

int Mesh1D::get_mesh_size() {
    return static_cast<int>(node_vector.size());
}

Node1D* Mesh1D::get_node(int node_id) {
    return &node_vector.at(node_id);
}

void Mesh1D::display_mesh_data(){
    int mesh_size = get_mesh_size();
    printf("Mesh size: %d\n", mesh_size);
    printf("Displaying cell information:\n");
    for(int cell_id=0; cell_id<mesh_size - 1; cell_id++){
        cell_vector.at(cell_id).display_cell_data();
    };
    printf("\n");

    printf("Displaying node information:\n");
    for (int node_id = 0; node_id < mesh_size; node_id++) {
        node_vector.at(node_id).display_node_data();
    };
    printf("\n");
}

void Mesh1D::to_csv(std::string mesh_name){
    std::string node_filename = mesh_name + node_file_extension;
    FILE* node_file = fopen(node_filename.c_str(), "w");

    //fprintf(node_file, "\n");

    fprintf(node_file, "A_west %lf, A_east %lf\n", west_area, east_area);
    fprintf(node_file, "x_west %lf, x_east %lf\n", west_x, east_x);
    for (int node_id = 0; node_id < node_vector.size(); node_id++) {
        Node1D node_to_print = node_vector.at(node_id);
        write_node_to_csv(node_file, node_to_print);
    };

    fclose(node_file);
};

double Mesh1D::get_west_x(){
    return west_x;
}
double Mesh1D::get_east_x() {
    return east_x;
}

double Mesh1D::get_west_area(){
    return west_area;
}

double Mesh1D::get_east_area() {
    return east_area;
}