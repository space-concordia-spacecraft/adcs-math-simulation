#pragma once

// Imports
#include <adcs/Constants.h>
#include <glm/glm.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat3;

// Table of content
namespace adcs::controls {

    bool eclipse_prediction(vec3 se, vec3 pe);
    void body_earth_estimation();
    void torque_saturation(const double tw[3], double out[3]);
    void saturation_rw(const double lw[3], const double ti[3], double out[3]);
    void selector(int mode, const double lwheel[3], const double nominal[3], const double calibration[3], double out[3]);
    vec3 targetFrameVelocity(vec4 quaternion_earth_target);

}