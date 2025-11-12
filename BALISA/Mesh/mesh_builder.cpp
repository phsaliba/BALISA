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
