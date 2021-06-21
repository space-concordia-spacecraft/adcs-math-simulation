#include <iostream>
#include <memory>

#include "matplotlibcpp.h"
#include "open3d/Open3D.h"
#include "adcs/Constants.h"
#include "old/TrueEquatorMeanEquinox.h"
#include "old/DTM_12.h"
#include "old/EopSpw.h"
#include "old/MathTimeLib.h"
#include "adcs/MSIS_Vers.h"
<<<<<<< HEAD:src/old/Main.cpp
#include "old/SGP4.h"
#include "adcs/SGP4DC.h"
=======
#include "adcs/SGP4.h"
//#include "adcs/SGP4DC.h"
>>>>>>> 728f27d891b35e599c76b0d3bbfafadf11b43c53:src/adcs/Main.cpp

#include "simulation/Simulation.h"
#include "old/ADCS.h"

namespace plt = matplotlibcpp;

using namespace open3d;
using adcs::simulation::Simulation;
using adcs::ADCS;

void runSimulation(Simulation * sim) {
    ADCS adcs(sim);
    adcs.run();
}

typedef glm::mat<8, 8, float, glm::defaultp> mat8;

int main(int argc, char *argv[]) {
    Simulation sim;

    std::thread second(runSimulation, &sim);

    sim.run();
    second.join();

    mat8 a;

    return 0;
}

void test() {
	
}