from typing import List

class BoundaryConditions1D():
    def __init__(self, phi_west_BC: float,phi_east_BC: float):
        self.phi_west_BC = phi_west_BC
        self.phi_east_BC = phi_east_BC

def steady_conduction_1d_bc(phi_west_BC: float, phi_east_BC: float):
    return BoundaryConditions1D(phi_west_BC, phi_east_BC)