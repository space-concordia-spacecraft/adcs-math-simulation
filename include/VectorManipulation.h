#pragma once

#include <Constants.h>
#include <DateTime.h>
#include <glm/glm.hpp>
using glm::vec3;
using glm::mat3;

namespace adcs {

    vec3 getSunPosition();
    vec3 mod2eci(vec3 pos, int julianCenturies);
    vec3 eci2teme();
    vec3 teme2ecef(vec3 steme, vec3 rteme, vec3 vteme, vec3 ateme, int julianCenturies, int julianDate, int lod, double xp, double yp, int eqeterms);
}
