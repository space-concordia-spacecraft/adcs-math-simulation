//
// Created by Charles on 4/9/2021.
//

#pragma once

#include <glm/glm.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using glm::normalize;
using glm::cross;
using glm::mat;
using glm::vec;
using glm::defaultp;

namespace adcs {

    typedef mat<7, 7, float, defaultp>            mat7;
    typedef mat<6, 6, float, defaultp>            mat6;
    typedef mat<6, 7, float, defaultp>            mat67;
    typedef mat<3, 6, float, defaultp>            mat36;
    typedef mat<6, 3, float, defaultp>            mat63;
    typedef vec<7, float, defaultp>               vec7;
    typedef vec<6, float, defaultp>               vec6;

    void triad(mat3 &dcm_AB,vec3 va1,vec3 va2,vec3 vb1,vec3 vb2);
    vec4 DCM2quat(mat3 dcm_AB);
    vec4 quat_multiply(vec4 qa, vec4 qb);
    vec3 quat_rotation(vec3 be, vec4 cq_be);

}
