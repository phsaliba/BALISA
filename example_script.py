# %%
from Mesh import mesh_1d
from Solver import boundary_conditions_1d, diffusion_equations_1d

# mesh = mesh_1d.create_constant_section_mesh_1d(domain_length=0.5, cross_section=0.01, n_nodes=5)
mesh = mesh_1d.create_linear_section_mesh1D(domain_length=0.5, inlet_section=0.05, outlet_section=0.01, n_nodes=100)

boundary_conditions = boundary_conditions_1d.steady_conduction_1d_bc(phi_west_BC=100, phi_east_BC=500)

solver = diffusion_equations_1d.SteadyDiffusion1D(mesh, boundary_conditions, diffusion_coef=1000, varname="T")
solver.solve()
solver.display_solution()
# %%
