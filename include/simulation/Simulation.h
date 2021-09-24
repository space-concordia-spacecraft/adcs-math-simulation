#pragma once

#include "open3d/Open3D.h"
#include "math.h"


using open3d::visualization::Visualizer;
using open3d::visualization::VisualizerWithKeyCallback;
using open3d::visualization::DrawGeometriesWithAnimationCallback;
using open3d::visualization::DrawGeometriesWithKeyCallbacks;
using open3d::geometry::TriangleMesh;
using open3d::io::ReadTriangleMesh;
using open3d::utility::LogWarning;
using open3d::utility::LogInfo;

class Simulation{
private:
    std::shared_ptr<TriangleMesh> cubeSat_ptr = nullptr;
    std::shared_ptr<TriangleMesh> earth_ptr = nullptr;
    std::shared_ptr<TriangleMesh> coordinate_Frame = nullptr;
    open3d::visualization::VisualizerWithKeyCallback vis;
    bool rotateFlag=false;
    bool revolveFlag =false;

    bool animationKeyCallback(Visualizer* vis);
    static bool rotationToggle(Visualizer* vis);
    static bool revolutionToggle(Visualizer* vis);
    static bool rotateSatelliteAntiClockwise(Visualizer* vis);
    static bool rotateSatelliteClockwise(Visualizer* vis);
    static Simulation * activeSimulation;
    bool ReadMeshes();
    bool Initialize();

public:
    Simulation();
    ~Simulation();

    Eigen::Vector3d rotation;

    int run();
    void setRotation(Eigen::Vector3d &rot);
    static bool _animationCallback(Visualizer * vis);
};