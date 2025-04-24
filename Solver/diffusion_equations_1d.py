import numpy as np

from Mesh.mesh_1d import *
from Solver.boundary_conditions_1d import *

class SteadyDiffusion1D():
    def __init__(self, mesh: Mesh1D, boundary_conditions: BoundaryConditions1D, diffusion_coef: float, varname="phi"):
        self.mesh = mesh
        self.nb_nodes = len(mesh.nodes)
        self.boundary_conditions = boundary_conditions
        self.diffusion_coef = diffusion_coef
        self.varname = varname

        self.coefficient_matrix = self.set_diffusion_equation_coefs()
        self.boundary_condition_vector = self.set_boundary_conditions()
        self.solution = None

    def set_diffusion_equation_coefs(self):        
        # Central differencing scheme
        # Computing generic a_W, a_E = a_WE_nodes since dx is constant:
        node_list = self.mesh.nodes
        a_WE_nodes = [self.diffusion_coef * node.cross_section_node / node.dx_node for node in node_list]
        
        a_P_middle_nodes = [a_WE_nodes[node_id - 1] + a_WE_nodes[node_id + 1]  for node_id in range(1, self.nb_nodes - 1)]

        a_P_west_node = a_WE_nodes[1] + 2 * self.diffusion_coef * node_list[0].cross_section_node / node_list[0].dx_node
        a_P_east_node = a_WE_nodes[-2] + 2 * self.diffusion_coef * node_list[-1].cross_section_node / node_list[-1].dx_node

        a_P_nodes = [a_P_west_node, *a_P_middle_nodes, a_P_east_node]

        coefficient_matrix = np.zeros((self.nb_nodes, self.nb_nodes))
        for node_id in range(self.nb_nodes):
            coefficient_matrix[node_id, node_id] = a_P_nodes[node_id]
            if node_id != self.nb_nodes - 1:
                coefficient_matrix[node_id, node_id + 1] = -a_WE_nodes[node_id + 1]
            if node_id != 0:
                coefficient_matrix[node_id, node_id - 1] = -a_WE_nodes[node_id - 1]

        return coefficient_matrix
    
    def set_boundary_conditions(self):
        boundary_condition_vector = np.zeros(self.nb_nodes)
        boundary_condition_vector[0] = 2 * self.diffusion_coef * self.mesh.cross_section_west * self.boundary_conditions.phi_west_BC / self.mesh.nodes[0].dx_node
        boundary_condition_vector[-1] = 2 * self.diffusion_coef * self.mesh.cross_section_east * self.boundary_conditions.phi_east_BC / self.mesh.nodes[-1].dx_node
        return boundary_condition_vector

    def solve(self):
        solution = np.matmul(np.linalg.inv(self.coefficient_matrix), self.boundary_condition_vector)
        for node_value, node in zip(solution, self.mesh.nodes):
            node.vars[self.varname] = node_value
        self.solution = solution
    

    def display_solution(self):
        assert self.solution is not None, "You must solve your problem before displaying the solution"
        x_position_list = [0., *[display_node.x_node for display_node in self.mesh.nodes], self.mesh.domain_length]
        value_list = [self.boundary_conditions.phi_west_BC, *self.solution, self.boundary_conditions.phi_east_BC]
        
        plt.plot(
            x_position_list,
            value_list,
            '-o',
            color="black",
        )
        plt.xlabel("X")
        plt.ylabel(self.varname)
        plt.show()




            

        
