#pragma once

#include <adcs/Constants.h>
#include <glm/glm.hpp>
using glm::dvec3;
using glm::dmat3;

namespace adcs::controls {
    typedef enum
    {
        detumbling,
        nadir_pointing,
        imaging_argentina,
        imaging_namibia,
        ground,
        sun,
        calibration,
        off
    } adcs_mode;

    bool eclipse_prediction(dvec3 se, dvec3 pe);
    void body_earth_estimation();
}
