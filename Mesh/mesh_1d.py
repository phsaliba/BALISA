import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
from typing import List

from Mesh.node_1d import Node1D

def equally_spaced_nodes(domain_length, n_nodes) -> np.array:
    dx = domain_length / n_nodes
    return np.arange(dx / 2, domain_length, dx)

class Mesh1D():
    def __init__(self, nodes: List[Node1D], west_bc: Node1D, east_bc: Node1D):
        self.nodes = nodes
        self.west_bc = west_bc
        self.east_bc = east_bc
        self.domain_length = east_bc.x - west_bc.x

    def display_mesh(self):        
        x_position_list = np.array([0., *[display_node.x for display_node in self.nodes], self.domain_length])
        node_center_list = np.zeros_like(x_position_list)
        plt.plot(
            x_position_list,
            node_center_list,
            '-o',
            color="black",
        )
        node_upper_list = np.array([self.west_bc.cross_section / 2, *[display_node.cross_section / 2 for display_node in self.nodes], self.east_bc.cross_section / 2])
        node_lower_list = -node_upper_list
        plt.plot(
            x_position_list,
            node_upper_list,
            '--',
            color="black",
        )
        plt.plot(
            x_position_list,
            node_lower_list,
            '--',
            color="black",
        )
        plt.show()

    def save_mesh(self, mesh_path: Path):
        with mesh_path.open("w") as mesh_file:
            self.west_bc.to_csv(mesh_file)
            for node in self.nodes:
                node.to_csv(mesh_file)
            self.east_bc.to_csv(mesh_file)


def create_constant_section_mesh_1d(
    domain_length: float,
	cross_section: float,
	n_nodes: float,
) -> Mesh1D:
    x_positions_mesh = equally_spaced_nodes(domain_length, n_nodes)
    cross_sections_mesh = np.ones_like(x_positions_mesh) * cross_section
    return create_custom_mesh1D(domain_length, cross_section, cross_section, x_positions_mesh, cross_sections_mesh)


def create_linear_section_mesh1D(
    domain_length: float,
	inlet_section: float,
	outlet_section: float,
	n_nodes:float
) -> Mesh1D:
    x_positions_mesh = equally_spaced_nodes(domain_length, n_nodes)
    # cross_sections_mesh = np.linspace(inlet_section, outlet_section, n_nodes)
    cross_sections_mesh = inlet_section + equally_spaced_nodes((outlet_section - inlet_section), n_nodes)

    return create_custom_mesh1D(domain_length, inlet_section, outlet_section, x_positions_mesh, cross_sections_mesh)

def create_custom_mesh1D(
        domain_length: float,
        inlet_section: float,
        outlet_section: float,
        x_positions_mesh: np.array,
        cross_sections_mesh: np.array
    ) -> Mesh1D:
    assert len(x_positions_mesh) == len(cross_sections_mesh), "x_position and cross_section arrays must have the same length"

    west_bc = Node1D(-1, 0., inlet_section)
    east_bc = Node1D(-1, domain_length, outlet_section)

    nodes = [Node1D(node_id, x_node, cross_section_node) for node_id, (x_node, cross_section_node) in enumerate(zip(x_positions_mesh, cross_sections_mesh))]
    return Mesh1D(nodes, west_bc, east_bc)