#pragma once

#include <adcs/Constants.h>
#include <glm/glm.hpp>
using glm::dvec3;
using glm::dmat3;

namespace adcs::controls {

    bool eclipse_prediction(dvec3 se, dvec3 pe);
    void body_earth_estimation();
    void torque_saturation(const double tw[3], double out[3]);
    void saturation_rw(const double lw[3], const double ti[3], double out[3]);
    void selector(int mode, const double lwheel[3], const double nominal[3], const double calibration[3], double out[3]);
    vec4 momentum_bias(dvec3 ve, dvec3 pe, dquat cbe)
}
