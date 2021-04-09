//
// Created by Charles on 4/9/2021.
//

#pragma once

#include <glm/glm.hpp>

using glm::vec3;
using glm::vec4;
using glm::dvec4;
using glm::mat3;
using glm::normalize;
using glm::cross;
using glm::mat;

typedef mat<7, 7, float, defaultp>            mat7;
typedef mat<6, 6, float, defaultp>            mat6;

namespace adcs {
    void triad(double &DCM_AB,vec3 va1,vec3 va2,vec3 vb1,vec3 vb2);

    vec4 filtered_derivative(vec4 vector);
}
