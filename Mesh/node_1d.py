class Node1D():
    def __init__(self, x_node: float, dx_node: float, cross_section_node: float):
        self.x_node = x_node
        self.dx_node = dx_node
        self.cross_section_node = cross_section_node

        self.vars = dict()

    def update_var(self, updated_var_name: str, updated_var_value: float):
        self.vars[updated_var_name] = updated_var_value