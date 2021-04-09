//
// Created by Charles on 4/9/2021.
//

#pragma once

#include <glm/glm.hpp>

using glm::vec3;
using glm::dvec4;
using glm::mat3;
using glm::normalize;
using glm::cross;
using glm::mat;
using glm::transpose;
using glm::defaultp;

namespace adcs {

typedef mat<7, 7, float, defaultp>            mat7;
typedef mat<6, 6, float, defaultp>            mat6;

// R is the sensors noise
const mat6 R = transpose(mat6(1e-4,0,0,0,0,0, //covariance Sx
                              0,1e-4,0,0,0,0, //covariance Sy
                              0,0,1e-4,0,0,0, //covariance Sz
                              0,0,0,2e-14,0,0, //covariance Bx
                              0,0,0,0,2e-14,0, //covariance By
                              0,0,0,0,0,2e-14)); //covariance Bz

// RE is the noise from the sensors during the night (i.e. no sun sensors)
const mat3 RE = transpose(mat3(2e-14,0,0, //covariance Bx
                               0,2e-14,0, //covariance By
                               0,0,2e-14)); //covariance Bz

// Q is the process noise (error on prediction)
const mat7 Q = transpose(mat7(5e-5,0,0,0,0,0,0,
                              0,5e-5,0,0,0,0,0,
                              0,0,5e-5,0,0,0,0,
                              0,0,0,5e-5,0,0,0,
                              0,0,0,0,2e-8,0,0,
                              0,0,0,0,0,2e-8,0,
                              0,0,0,0,0,0,2e-8));

    void triad(double &DCM_AB,vec3 va1,vec3 va2,vec3 vb1,vec3 vb2);
}
