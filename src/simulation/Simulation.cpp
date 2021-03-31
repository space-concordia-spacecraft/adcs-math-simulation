#include "simulation/Simulation.h"

namespace adcs::simulation {
    Simulation* Simulation::activeSimulation = nullptr;

    Simulation::Simulation():rotation(0,0,0),mesh_ptr(std::make_shared<TriangleMesh>()){
        if(activeSimulation != nullptr) {
            delete activeSimulation;
        }

        activeSimulation = this;
    }

    Simulation::~Simulation(){
        if(activeSimulation == this) {
            activeSimulation = nullptr;
        }
    }

    int Simulation::run() {

        if (ReadTriangleMesh("./assets/models/sc_odin_budget.ply", *mesh_ptr)) {
            LogInfo("Successfully read mesh\n");
        } else {
            LogWarning("Failed to read mesh\n\n");
            return 1;
        }

        mesh_ptr->ComputeVertexNormals();

        DrawGeometriesWithAnimationCallback({mesh_ptr}, Simulation::_animationCallback);
        return 0;
    }

    void Simulation::setRotation(Eigen::Vector3d &rot){
        rotation = Eigen::Vector3d(rot);
    }

    bool Simulation::animationCallback(Visualizer * vis) {
        auto R = TriangleMesh::CreateCoordinateFrame()->GetRotationMatrixFromXYZ(rotation);
        mesh_ptr->Rotate(R, Eigen::Vector3d(0, 0, 0));
        vis->UpdateGeometry({mesh_ptr});
        return false;
    }

    bool Simulation::_animationCallback(Visualizer * vis) {
        if(activeSimulation != nullptr) {
            return activeSimulation->animationCallback(vis);
        }
        return false;
    }
}