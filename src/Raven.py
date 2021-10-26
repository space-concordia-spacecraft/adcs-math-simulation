import time
import threading
import open3d as o3d
import open3d.visualization.gui as gui
import numpy as np
import os

DIR_NAME = os.path.dirname(os.path.abspath(__file__))
ODIN_MODEL = "\\..\\assets\\models\\sc_odin_budget.ply"
EARTH_MODEL = "\\..\\assets\\models\\earth_mesh.ply"

class Raven:

    cubeSatMesh = None
    earthMesh = None
    windowLayout = []
    sceneLayout = []
    materialShader = None
    sim = None

    #todo: Log the Steps taken by Raven.
    def __init__(self):
        self.sim = gui.Application.instance
        self.sim.initialize()
        self.create_window_layout()
        self.create_shader()
        self.cubeSatMesh = self.read_mesh(DIR_NAME + ODIN_MODEL)
        self.earthMesh = self.read_mesh(DIR_NAME + EARTH_MODEL)
        self.colour_meshes()
        self.initialize_scene()
        self.add_meshes()
        self.setup_background()
        self.setup_scene_camera()

    def threading(self):
        while True:
            self.update_geometry()
            self.rotate_geometry()

            self.sim.post_to_main_thread(self.windowLayout[0], self.update_geometry())
            self.sim.post_to_main_thread(self.windowLayout[1], self.update_geometry())
            time.sleep(0.10)

    def run(self):
       self.sim.run()

    def read_mesh(self, fileName):
        pcd = o3d.io.read_triangle_mesh(fileName)
        pcd = pcd.compute_vertex_normals()
        return pcd

    def on_mouse(e):
        if e.type == gui.MouseEvent.Type.BUTTON_DOWN:
            print("[debug] mouse:", (e.x, e.y))
        return gui.Widget.EventCallbackResult.IGNORED

    def on_key(e):
        if e.key == gui.KeyName.SPACE:
            if e.type == gui.KeyEvent.UP:  # check UP so we default to DOWN
                print("[debug] SPACE released")
            else:
                print("[debug] SPACE pressed")
            return gui.Widget.EventCallbackResult.HANDLED
        if e.key == gui.KeyName.W:  # eats W, which is forward in fly mode
            print("[debug] Eating W")
            return gui.Widget.EventCallbackResult.CONSUMED
        return gui.Widget.EventCallbackResult.IGNORED

    def create_window_layout(self):
        self.windowLayout.append(gui.Application.instance.create_window("Perspective 1", 640, 480))
        self.windowLayout.append(gui.Application.instance.create_window("Perspective 2", 640, 480))
        self.windowLayout.append(gui.Application.instance.create_window("Perspective 3", 640, 480))
        self.create_scene_layout()
        self.link_window_to_renderer()
        return False

    def create_scene_layout(self):
        self.sceneLayout.append(gui.SceneWidget())
        self.sceneLayout[0].scene = o3d.visualization.rendering.Open3DScene(self.windowLayout[0].renderer)
        return False

    def link_window_to_renderer(self):
        self.windowLayout[0].add_child(self.sceneLayout[0])
        return False

    def create_shader(self):
        self.materialShader = o3d.visualization.rendering.Material()
        self.materialShader.shader = "defaultLit"
        return False

    def colour_meshes(self):
        self.earthMesh.paint_uniform_color([0.6784, 0.8471, 0.902])
        self.cubeSatMesh.paint_uniform_color([0.5568, 0.5568, 0.5568])

    def add_meshes(self):
        self.sceneLayout[0].scene.add_geometry("CubeSat", self.cubeSatMesh, self.materialShader)
        self.sceneLayout[0].scene.add_geometry("Earth", self.earthMesh, self.materialShader)
        return False

    def setup_scene_camera(self):
        self.sceneLayout[0].setup_camera(60, self.sceneLayout[0].scene.bounding_box, (0, 0, 0))

    def setup_callback(self):
        self.sceneLayout[0].set_on_mouse(self.on_mouse)
        self.sceneLayout[0].set_on_key(self.on_key)
        return False

    def setup_background(self):
        self.sceneLayout[0].scene.set_background(np.array([0.0, 0.0, 0.0, 1.0]))

    def clear_geometry(self):
        self.sceneLayout[0].scene.clear_geometry()

    def update_geometry(self):
        self.clear_geometry()
        self.add_meshes()

    def rotate_geometry(self):
        orbital_motion = self.cubeSatMesh.get_rotation_matrix_from_xyz((0, 0, np.pi/128))
        rotation_motion = self.cubeSatMesh.get_rotation_matrix_from_xyz((0, 0, np.pi/128))
        self.cubeSatMesh.rotate(rotation_motion, self.cubeSatMesh.get_center())

    def initialize_scene(self):
        self.cubeSatMesh.translate((50.0, 0.0, 0.0))
        self.cubeSatMesh.scale(0.1, self.cubeSatMesh.get_center())

    def wire_frame(self):
        self.cubeSatMesh = o3d.geometry.LineSet.create_from_triangle_mesh(self.cubeSatMesh)