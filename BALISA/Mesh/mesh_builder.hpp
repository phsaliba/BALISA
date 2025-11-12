#pragma once
#include "Mesh1D.hpp"

Mesh1D create_uniform_1d_mesh(int number_of_nodes, double total_length, double area);

// Mesh1D create_1d_mesh_from_csv(std::string mesh_name);
Mesh1D create_1d_mesh_from_csv(std::string mesh_name);