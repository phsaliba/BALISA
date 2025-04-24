import numpy as np
import matplotlib.pyplot as plt
from typing import List

from Mesh.node_2d import Node2D

def equally_spaced_nodes(domain_length, n_nodes):
    dx = domain_length / n_nodes
    return dx, np.arange(dx / 2, domain_length, dx)

class Mesh2D():
    def __init__(self, nodes: List[List[Node2D]], vertical_length: float, horizontal_length: float):
        self.nodes = nodes
        self.vertical_length = vertical_length
        self.horizontal_length = horizontal_length
        self.domain_length = domain_length

    def display_mesh(self):        
        raise NotImplementedError("be patient")


def create_square_mesh_1d(domain_length: float, n_nodes_per_side: float):
    dx, x_positions_mesh = equally_spaced_nodes(domain_length, n_nodes_per_side)

    nodes = []
    for y, dy in zip(x_positions_mesh, dx):
        nodes.append([Node2D(x_node, y, dx, dy) for x_node in x_positions_mesh])
    return Mesh2D(nodes=nodes, vertical_length=domain_length, horizontal_length=domain_length, vertical_length=domain_length)


def create_rectangular_mesh_2d(domain_length: float, vertical_length: float, horizontal_length: float, n_nodes_vertical: float, n_nodes_horizontal: float):
    dx, x_positions_mesh = equally_spaced_nodes(horizontal_length, n_nodes_horizontal)
    dy, y_positions_mesh = equally_spaced_nodes(vertical_length, n_nodes_vertical)

    nodes = []
    for y, dy in zip(y_positions_mesh, dy):
        nodes.append([Node2D(x_node, y, dx, dy) for x_node in x_positions_mesh])
    return Mesh2D(nodes=nodes, vertical_length=vertical_length, horizontal_length=horizontal_length)