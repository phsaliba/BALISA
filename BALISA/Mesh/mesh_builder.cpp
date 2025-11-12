#include<string>

#include "Mesh1D.hpp"
#include "mesh_file_helper.hpp"

Mesh1D create_uniform_1d_mesh(int number_of_nodes, double total_length, double area){
    std::vector<Node1D> uniform_node_vector;

    double node_size = total_length / number_of_nodes;
    for(int node_id = 0; node_id < number_of_nodes; node_id++){
        //printf("Creating node %d\n", node_id);
        double x_position = (node_id + 0.5) * node_size;
        Node1D new_node(node_id, x_position, area);
        uniform_node_vector.push_back(new_node);
    };
    Mesh1D uniform_1d_mesh(uniform_node_vector, area, area, 0., total_length);
    return uniform_1d_mesh;
}

Mesh1D create_1d_mesh_from_csv(std::string mesh_name){
    std::vector<Node1D> uniform_node_vector;

    int file_node_id;
    double file_x, file_area, file_p;
    double west_area, east_area, west_x, east_x;

    std::string node_filename = mesh_name + node_file_extension;
    FILE *node_file = fopen(node_filename.c_str(), "r");
    //auto junk = fscanf(node_file, node_file_header.c_str());
    auto junk = fscanf(node_file, "A_west %lf, A_east %lf\n", &west_area, &east_area);
    junk = fscanf(node_file, "x_west %lf, x_east %lf\n", &west_x, &east_x);
    while (fscanf(node_file, "%d, %lf, %lf, %lf", &file_node_id, &file_x, &file_area, &file_p) != EOF) {
        Node1D new_node(file_node_id, file_x, file_area);
        uniform_node_vector.push_back(new_node);
    };
    Mesh1D new_mesh(uniform_node_vector, west_area, east_area, west_x, east_x);
    return new_mesh;
}
