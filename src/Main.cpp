#include <iostream>
#include <memory>

#include "matplotlibcpp.h"
#include "open3d/Open3D.h"

#include "simulation/Simulation.h"

namespace plt = matplotlibcpp;

using namespace open3d;
using adcs::simulation::Simulation;

int main(int argc, char *argv[]) {
    Simulation sim;

    sim.run();

    return 0;
}