#pragma once

#include <Constants.h>
#include <glm/glm.hpp>
using glm::vec3;
using glm::mat3;
using glm::vec4;

namespace adcs::controls {
    void Guidance(int mode,vec3 se,vec3 pe,vec3 ve,vec3 ne,vec3 ae,vec3 ge,vec3 %pointingE,vec3 %constraintE,vec3 %pointingB,vec3 %constraintB);

}
