#pragma once

#include <glm/glm.hpp>

#include "Constants.h"

using glm::mat4;

namespace fsw {

    namespace math {
        double getJulianDate(int year, int month, int day, int hour, int min, int sec); // Julian Date
        mat4 getPolarMotionMatrix(float xp, float yp, int julianCenturiesTT, int mode); // Polar Motion Matrix
        double getGreenwichSiderealTime(int julianDate); // Greenwich Sidereal Time
    }

}