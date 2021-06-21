#pragma once

#include <adcs/Constants.h>

#include "simulation/Simulation.h"

#include "SimplifiedGeneralPerturbations.h"
#include "TrueEquatorMeanEquinox.h"
#include "Controls.h"
#include "Location.h"

#include <iostream>
#include <ctime>

#include "glm/glm.hpp"

using glm::vec3;

using adcs::simulation::Simulation;
using adcs::location::mod_eci;

namespace adcs {
    class ADCS{
    private:
        char longstr1[130], longstr2[130];
        Simulation *simulation;

    public:
        ADCS(Simulation *simulation);
        ~ADCS();

        void run();
        void setTLEs(char longstr1[130], char longstr2[130]);
    };

}
