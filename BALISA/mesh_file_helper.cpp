#include "Mesh/mesh_file_helper.hpp"

void write_node_to_csv(FILE* node_file, Node1D* node_to_print) {
	fprintf(node_file, "%d, %f, %f\n", node_to_print->get_id(), node_to_print->get_x(), node_to_print->get_area());
}
