#pragma once

#include <adcs/Constants.h>
#include <glm/glm.hpp>
using glm::vec3;
using glm::mat3;

namespace adcs::controls {

    vec3 generateMagneticField(vec3 dipole, vec3 body);
    void guidance(int mode, vec3 Se);

}
