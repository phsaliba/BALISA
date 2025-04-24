class Node1D():
    def __init__(self, x: float, dx: float, cross_section: float):
        self.x = x
        self.dx = dx
        self.cross_section = cross_section

        self.vars = dict()

    def update_var(self, updated_var_name: str, updated_var_value: float):
        self.vars[updated_var_name] = updated_var_value