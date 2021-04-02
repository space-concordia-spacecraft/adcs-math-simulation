#pragma once

#include <adcs/Constants.h>

#include "simulation/Simulation.h"

#include "adcs/SGP4.h"
#include "adcs/AstroLib.h"
#include "adcs/Controls.h"

using adcs::simulation::Simulation;

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
