#pragma once

#include <adcs/Constants.h>
#include "open3d/Open3D.h"

using open3d::visualization::Visualizer;
using open3d::visualization::DrawGeometriesWithAnimationCallback;
using open3d::geometry::TriangleMesh;
using open3d::io::ReadTriangleMesh;
using open3d::utility::LogWarning;
using open3d::utility::LogInfo;

namespace adcs::simulation {
    class Simulation{
    private:
        std::shared_ptr<TriangleMesh> mesh_ptr;


        bool animationCallback(Visualizer * vis);
        static Simulation * activeSimulation;

    public:
        Simulation();
        ~Simulation();

        Eigen::Vector3d rotation;

        int run();
        void setRotation(Eigen::Vector3d &rot);
        static bool _animationCallback(Visualizer * vis);
    };

}
