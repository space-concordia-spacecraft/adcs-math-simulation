#pragma once

#include "adcs/Constants.h"

namespace adcs {
    namespace controls {

        void torque_saturation(const double tw[3], double out[3]);
        void saturation_rw(const double lw[3], const double ti[3], double out[3]);
        void selector(int mode, const double lwheel[3], const double nominal[3], const double calibration[3], double out[3]);

    }
}
