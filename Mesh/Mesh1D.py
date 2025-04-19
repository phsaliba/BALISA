import numpy as np
import matplotlib.pyplot as plt
from typing import List

from Node1D import Node1D


class Mesh1D():
    def __init__(self, nodes: List[Node1D]):
        self.nodes = nodes

    def display_mesh(self):        
        x_position_list = [display_node.x_position_node for display_node in self.nodes]
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


class ConstantSectionMesh1D(Mesh1D):
    def __init__(self, length: float, cross_section: float, n_nodes: float):
        x_positions_mesh = np.linspace(0., length, n_nodes)

        nodes = [Node1D(x_position_node, cross_section) for x_position_node in x_positions_mesh]
        super().__init__(nodes=nodes)


class LinearSectionMesh1D(Mesh1D):
    def __init__(self, length: float, inlet_section: float, outlet_section: float, n_nodes:float):
        x_positions_mesh = np.linspace(0., length, n_nodes)
        cross_sections_mesh = np.linspace(inlet_section, outlet_section, n_nodes)

        nodes = [Node1D(x_position_node, cross_section_node) for x_position_node, cross_section_node in zip(x_positions_mesh, cross_sections_mesh)]
        super().__init__(nodes=nodes)
