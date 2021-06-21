#pragma once

#include "adcs/Constants.h"

/*     ----------------------------------------------------------------
*
*                                 DateTime.h
*/

namespace adcs::datetime {

    void jday(int year, int month, int day, int hour, int min, double sec, double julianDay, double julianDayFraction);

}