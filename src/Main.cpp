#include <iostream>
#include <memory>
#include <simulation/Simulation.h>
#include "matplotlibcpp.h"
#include "open3d/Open3D.h"
#include "glm/glm.hpp"
#include "math.h"

#include "open3d/Open3D.h"
namespace plt = matplotlibcpp;
using namespace open3d;

int main(int argc, char *argv[]){
    Simulation sim;

    sim.run();
    return 0;
}