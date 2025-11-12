#pragma once
#include <vector>
#include <string>
#include "Cell1D.hpp"

using std::string;
using std::vector;

class Mesh1D{
    public:
        Mesh1D(std::vector<Node1D> input_node_vector, double input_west_area, double input_east_area, double input_east_x, double input_west_x);

        int get_mesh_size();
        Node1D* get_node(int node_id);
        void display_mesh_data();
        void to_csv(string mesh_name);

        double get_west_x();
        double get_east_x();

        double get_west_area();
        double get_east_area();

        Node1D west_bc;
        Node1D east_bc;
    private:
        vector<Cell1D> cell_vector;
        vector<Node1D> node_vector;


        double west_x;
        double east_x;
        
        double west_area;
        double east_area;
};
