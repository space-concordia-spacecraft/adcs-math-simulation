#pragma once

#include <string>
#include <glm/glm.hpp>
using glm::vec3;

namespace adcs::sgp4 {
    struct Sgp4 {
        char satnum, classification, intldesg, epochyr, epochdays, ndot, nddot, bstar;
    };

    void initSgp4(char& tle1, char& tle2, Sgp4& sgp4);
    void runPredictionModel(int time, vec3& position, vec3& velocity);
}
