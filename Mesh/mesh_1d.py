import numpy as np
import matplotlib.pyplot as plt
from typing import List

from Mesh.node_1d import Node1D

def equally_spaced_nodes(domain_length, n_nodes):
    dx = domain_length / n_nodes
    return dx, np.arange(dx / 2, domain_length, dx)

class Mesh1D():
    def __init__(self, nodes: List[Node1D], cross_section_west: float, cross_section_east: float):
        self.nodes = nodes
        self.cross_section_west = cross_section_west
        self.cross_section_east = cross_section_east

    def display_mesh(self):        
        x_position_list = [display_node.x_node for display_node in self.nodes]
        node_center_list = np.zeros_like(x_position_list)
        plt.plot(
            x_position_list,
            node_center_list,
            '-o',
            color="black",
        )
        node_upper_list = [display_node.cross_section_node / 2 for display_node in self.nodes]
        node_lower_list = [-display_node.cross_section_node / 2 for display_node in self.nodes]
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


def create_constant_section_mesh_1d(domain_length: float, cross_section: float, n_nodes: float):
    dx, x_positions_mesh = equally_spaced_nodes(domain_length, n_nodes)

    nodes = [Node1D(x_node, dx, cross_section) for x_node in x_positions_mesh]
    return Mesh1D(nodes=nodes, cross_section_west=cross_section, cross_section_east=cross_section)


def create_linear_section_mesh1D(domain_length: float, inlet_section: float, outlet_section: float, n_nodes:float):
    dx, x_positions_mesh = equally_spaced_nodes(domain_length, n_nodes)
    cross_sections_mesh = np.linspace(inlet_section, outlet_section, n_nodes)

    nodes = [Node1D(x_node, dx, cross_section_node) for x_node, cross_section_node in zip(x_positions_mesh, cross_sections_mesh)]
    return Mesh1D(nodes=nodes, cross_section_west=inlet_section, cross_section_east=outlet_section)
