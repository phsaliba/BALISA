#include<iostream>
#include<stdio.h> 

#include<vector>
#include<string>

using std::string;
using std::vector;

#include "Mesh1D.hpp"
#include "mesh_file_helper.hpp"

Mesh1D::Mesh1D(
    vector<Node1D> input_node_vector,
    double input_west_area,
    double input_east_area,
    double input_east_x,
    double input_west_x
) :
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

Mesh1D::Mesh1D(
    vector<Node1D> input_node_vector,
    Node1D west_bc,
    Node1D east_bc
) :
    west_bc(west_bc),
    east_bc(east_bc)
{
    node_vector = input_node_vector;

    for (int cell_id = 0; cell_id < node_vector.size() - 1; cell_id++) {
        Cell1D new_cell(cell_id, &node_vector.at(cell_id), &node_vector.at(cell_id + 1));
        cell_vector.push_back(new_cell);
    }

    west_area = west_bc.get_area();
    east_area = east_bc.get_area();

    west_x = west_bc.get_x();
    east_x = east_bc.get_x();
}

Mesh1D::Mesh1D(string mesh_path) :
    west_bc(-1, 0., 0.),
    east_bc(-1, 0., 0.) 
{
    int file_node_id;
    double file_x, file_area, file_p;

    string node_info_str = "%d, %lf, %lf";

    FILE* mesh_file = fopen(mesh_path.c_str(), "r");
    string test;
    auto junk = fscanf(mesh_file, node_info_str.c_str(), &file_node_id, &file_x, &file_area);
    west_bc = Node1D(file_node_id, file_x, file_area);
    junk = fscanf(mesh_file, node_info_str.c_str(), &file_node_id, &file_x, &file_area);
    while (file_node_id != -1 && junk != EOF) {
        Node1D new_node(file_node_id, file_x, file_area);
        node_vector.push_back(new_node);
        junk = fscanf(mesh_file, node_info_str.c_str(), &file_node_id, &file_x, &file_area);
    };
    east_bc = Node1D(file_node_id, file_x, file_area);

    for (int cell_id = 0; cell_id < node_vector.size() - 1; cell_id++) {
        Cell1D new_cell(cell_id, &node_vector.at(cell_id), &node_vector.at(cell_id + 1));
        cell_vector.push_back(new_cell);
    }

    west_area = west_bc.get_area();
    east_area = east_bc.get_area();

    west_x = west_bc.get_x();
    east_x = east_bc.get_x();
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

    write_node_to_csv(node_file, west_bc);
    for (int node_id = 0; node_id < node_vector.size(); node_id++) {
        Node1D node_to_print = node_vector.at(node_id);
        write_node_to_csv(node_file, node_to_print);
    };
    write_node_to_csv(node_file, east_bc);

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