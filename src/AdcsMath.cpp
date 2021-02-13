//
// Created by Ruben on 2/12/2021.
//

#include "AdcsMath.h"
#include <cmath>

namespace fsw::math {

    double getJulianDate(int year, int month, int day, int hour, int min, int sec) {
        return (367.0 * year - floor( ( 7 * ( year + floor( (month + 9 ) / 12.0) ) ) * 0.25)) +
               ((sec + min * 60 + hour * 3600.0)/86400.0);
    }

    /**
     * Function to calculate the transformation matrix that accounts for polar motion.
     * @param xp - polar motion coefficient
     * @param yp - polar motion coefficient
     * @param julianCenturiesTT - Julian Centuries of Terrestrial Time
     * @param mode - method mode 1, 2, 80
     * @return - polar motion matrix
     **/
    mat4 getPolarMotionMatrix(float xp, float yp, int julianCenturiesTT, int mode) {
        double cosxp = cos(xp);
        double sinxp = sin(xp);
        double cosyp = cos(yp);
        double sinyp = sin(yp);

        if(mode == 80) {

        } else {
            double sp = -47.0e-6 * julianCenturiesTT * (CONST_PI / (3600.0*180.0));
            double cossp = cos(sp);
            double sinsp = sin(sp);
        }

        return {};
    }

    /**
     * Function to find the Greenwich Sidereal Time
     * @param julianDate - julian date
     * @return - the greenwich sidereal time (0 to 2PI)
     **/
    double getGreenwichSiderealTime(int julianDate) {
        double julianCenturies = (julianDate - 2451545.0) / 36525.0;

        double gst = - 6.2e-6 * pow(julianCenturies,3) + 0.093104 * pow(julianCenturies,2)
                     + (876600.0 * 3600.0 + 8640184.812866) * julianCenturies + 67310.54841;

        gst = fmod(gst * CONST_PI / 180.0, 2 * CONST_PI);

        if(gst < 0.0)
            gst += (2 * CONST_PI);

        return gst;
    }

}