//
// Created by Ruben on 2/12/2021.
//

#pragma once

#include "fsw/AdcsDriver/AdcsMath.hpp"

namespace fsw {

    class AdcsMath {

    public:

        // ----------------------------------------------------------------------
        // Construction, initialization, and destruction
        // ----------------------------------------------------------------------

        //! Construct object AdcsMath
        //!
        AdcsMath();

        //! Destroy object AdcsMath
        //!
        ~AdcsMath();

        // Constants

        extern const double GRAVITATIONAL_CONSTANT;
        extern const double MASS_OF_EARTH;

        extern const float SUNLIT_AREA;
        extern const double SPEED_OF_LIGHT;
        extern const float UNITLESS_REFLECTANCE_FACTOR;
        extern const int SOLAR_CONSTANT;

        extern const double PI;

        float getJulianDate(int year, int month, int day, int hour, int min, int sec); // Julian Date
        mat4 getPolarMotionMatrix(float xp, float yp, int julianCenturiesTT, int mode); // Polar Motion Matrix
        float getGreenwichSiderealTime(int julianDate); // Greenwich Sidereal Time


    private:

    };

}