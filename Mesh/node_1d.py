class Node1D():
    def __init__(self, node_id: int, x: float, cross_section: float):
        self.node_id = node_id
        self.x = x
        self.cross_section = cross_section

    def to_csv(self, mesh_file):
        mesh_file.write(f"{self.node_id} {self.x} {self.cross_section}\n")