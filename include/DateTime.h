#pragma once
#include "Constants.h"

namespace adcs::datetime {
    double getJulianDate(int year, int month, int day, int hour, int min, int sec); // Julian Date
    double getGreenwichSiderealTime(int julianDate); // Greenwich Sidereal Time
}
