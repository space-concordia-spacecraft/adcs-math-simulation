//
// Created by Ruben on 2/12/2021.
//

#include "adcs/Location.h"

namespace adcs::location {

    void sunalmanac(double jdtdb, double jdtdbF, vec3 rsun, double& rtasc, double& decl) {
        double deg2rad;
        double tut1, meanlong, ttdb, meananomaly, eclplong, obliquity, magr;

        double twopi = CONST_PI * 2.0f;

        deg2rad = CONST_PI / 180.0;

        // -------------------------  implementation   -----------------
        // -------------------  initialize values   --------------------
        tut1 = (jdtdb + jdtdbF - 2451545.0) / 36525.0;

        meanlong = 280.460 + 36000.77 * tut1;
        meanlong = fmod(meanlong, 360.0);  //deg

        ttdb = tut1;
        meananomaly = 357.5277233 + 35999.05034 * ttdb;
        meananomaly = fmod(meananomaly * deg2rad, twopi);  //rad
        if (meananomaly < 0.0)
        {
            meananomaly = twopi + meananomaly;
        }
        eclplong = meanlong + 1.914666471 * sin(meananomaly)
                   + 0.019994643 * sin(2.0 * meananomaly); //deg
        obliquity = 23.439291 - 0.0130042 * ttdb;  //deg
        meanlong = meanlong * deg2rad;
        if (meanlong < 0.0)
        {
            meanlong = twopi + meanlong;
        }
        eclplong = eclplong * deg2rad;
        obliquity = obliquity * deg2rad;

        // --------- find magnitude of sun vector, ) components ------
        magr = 1.000140612 - 0.016708617 * cos(meananomaly)
               - 0.000139589 * cos(2.0 *meananomaly);    // in au's

        rsun[0] = magr * cos(eclplong);
        rsun[1] = magr * cos(obliquity) * sin(eclplong);
        rsun[2] = magr * sin(obliquity) * sin(eclplong);

        rtasc = atan(cos(obliquity) * tan(eclplong));

        // --- check that rtasc is in the same quadrant as eclplong ----
        if (eclplong < 0.0)
        {
            eclplong = eclplong + twopi;    // make sure it's in 0 to 2pi range
        }
        if (fabs(eclplong - rtasc) > CONST_PI * 0.5)
        {
            rtasc = rtasc + 0.5 * CONST_PI * round((eclplong - rtasc) / (0.5 * CONST_PI));
        }
        decl = asin(sin(obliquity) * sin(eclplong));

    }  // sunalmanac

    // -----------------------------------------------------------------------------
    // round a number to the nearest integer
    double round(double x) {
        double temp;
        temp = floor(x + 0.5);
        return int(temp);
    }  // round

    void mod_eci(vec3 rsun, double julianCenturies, vec3 reci) {
        mat3 prec = precess(julianCenturies);
        reci = rsun * prec;
    }

    void eci_teme(int ddpsi, int ddeps, vec3 reci, double nut80, double julianCenturies, vec3 rteme){
        mat3 prec = precess(julianCenturies);
    }

    void xyz_ell3(vec3 position, double &latitude, double &longitude, double &altitude, double &h) {
        double a = 6378137.0;
        double finv = 298.257222101;

        double f = 1 / finv;
        double b = a * (1 - f);
        double e2 = 1 - pow((1 - f), 2);

        longitude = atan2(position.y,position.x); //longitude
        double e = e2*pow((a/b),2);
        double p = sqrt((pow(position.x, 2))+pow(position.y, 2));
        double r = sqrt(pow(p, 2)+pow(position.z, 2));
        double u = atan(b*position.z*(1+e*b/r)/(a*p));
        latitude = atan((position.z+(e*b*pow(sin(u),3) ))/(p-(e2*a*pow(cos(u),3)))); // latitude
        double v = a/sqrt(1-(e2*pow(sin(latitude),2) ));
        h = p*cos(latitude)+position.z*sin(latitude)-a*a/v;
        altitude = r; // altitude
    }

    void igrfs(double latitude, double longitude, double altitude, vec3 &position) {
        double costheta = cos(((CONST_PI / 2.0)- latitude));
        double sintheta = sin(((CONST_PI / 2.0)- latitude));

        double r = altitude;
        double phi = longitude;

        mat14 gh = mat14(-29442, -1501, 4797.1, -2445.1, 3012.9, -2845.6, 1676.7, -641.9, 1350.7, -2352.3, -115.3, 1225.6, 244.9, 582, -538.4, 907.6, 813.7, 283.3, 120.4, -188.7, -334.9, 180.9, 70.4, -329.5, -232.6, 360.1, 47.3, 192.4, 197, -140.9, -119.3, -157.5, 16, 4.1, 100.2, 70, 67.7, -20.8, 72.7, 33.2, -129.9, 58.9, -28.9, -66.7, 13.2, 7.3, -70.9, 62.6, 81.6, -76.1, -54.1, -6.8, -19.5, 51.8, 5.7, 15, 24.4, 9.4, 3.4, -2.8, -27.4, 6.8, -2.2, 24.2, 8.8, 10.1, -16.9, -18.3, -3.2, 13.3, -20.6, -14.6, 13.4, 16.2, 11.7, 5.7, -15.9, -9.1, -2, 2.1, 5.4, 8.8, -21.6, 3.1, 10.8, -3.3, 11.8, 0.7, -6.8, -13.3, -6.9, -0.1, 7.8, 8.7, 1, -9.1, -4, -10.5, 8.4, -1.9, -6.3, 3.2, 0.1, -0.4, 0.5, 4.6, -0.5, 4.4, 1.8, -7.9, -0.7, -0.6, 2.1, -4.2, 2.4, -2.8, -1.8, -1.2, -3.6, -8.7, 3.1, -1.5, -0.1, -2.3, 2, 2, -0.7, -0.8, -1.1, 0.6, 0.8, -0.7, -0.2, 0.2, -2.2, 1.7, -1.4, -0.2, -2.5, 0.4, -2, 3.5, -2.4, -1.9, -0.2, -1.1, 0.4, 0.4, 1.2, 1.9, -0.8, -2.2, 0.9, 0.3, 0.1, 0.7, 0.5, -0.1, -0.3, 0.3, -0.4, 0.2, 0.2, -0.9, -0.9, -0.1, 0, 0.7, 0, -0.9, -0.9, 0.4, 0.4, 0.5, 1.6, -0.5, -0.5, 1, -1.2, -0.2, -0.1, 0.8, 0.4, -0.1, -0.1, 0.3, 0.4, 0.1, 0.5, 0.5, -0.3, -0.4, -0.4, -0.3, -0.8);

        gh = transpose(gh);
        double nmax = sqrt(195) -1;

    }

    void lg2ct(vec3 position, double latitude, double longitude, vec3 &coordinateDifferences) {

    }

    void itrf_body(vec3 be, vec3 ve, vec3 pe, vec3 se, mat3 dcm_be, vec3 &b, vec3 &v, vec3 &p, vec3 &s) {
        double angle = acos(glm::dot(se, pe)/(glm::length(se)*glm::length(pe))) * 180.0 / CONST_PI;

        b = be * dcm_be;
        v = ve * dcm_be;
        p = pe * dcm_be;

        if(angle > 109.79)
            s = vec3(0,0,0);
        else
            s = se * dcm_be;
    }

    void disturbance_torque(vec3 dipoleMoment, vec3 b, vec3 p, vec3 inertiaMatrix, vec3 s, vec3 v, double h, vec3 &torqueDisturbance){
        // magnetic field
        vec3 magneticField = glm::cross(dipoleMoment, (1e-9 * b));

        // gravity gradient
        p *= 1000;

        double tempdot = glm::dot(p,p);
        double thirdTerm = pow(tempdot, 2.5);

        vec3 temp = p * inertiaMatrix;
        vec3 fourthTerm = glm::cross(temp, p);

        vec3 gravityGradient = vec3(1,1,1);
        gravityGradient *= CONST_GRAVITATIONAL_CONSTANT;
        gravityGradient *= 3;
        gravityGradient *= thirdTerm;
        gravityGradient *= fourthTerm;

        // solar radiation pressure

        // atmospheric drag

    }

    void teme_ecef(vec3 steme, vec3 rteme, vec3 vteme, vec3 ateme,
                   double julianCenturies, double jdut1,
                   vec3 &secef, vec3 &recef, vec3 &vecef, vec3 &aecef, mat3 &DCM_ET,
                   double lod, double xp, double yp, int eqeterms) {
        double omega, gmstg, thetasa, gmst;

        vec3 omegaearth, rpef, vpef, apef, spef, omgxr, omgxomgxr, omgxv, tempvec1, tempvec, temp;

        mat3 st, stdot, pm, pmp, stp;

        gmst = gstime(jdut1);

        // find omeage from nutation theory
        omega = 125.04452222 + (-6962890.5390 * julianCenturies + 7.455 *julianCenturies*julianCenturies + 0.008 *julianCenturies*julianCenturies*julianCenturies) / 3600.0;
        omega = fmod(omega, 360.0) * CONST_DEG_TO_RAD;

        // teme does not include the geometric terms here
        // after 1997, kinematic terms apply
        if ((jdut1 > 2450449.5) && (eqeterms > 0))
        {
            gmstg = gmst
                    + 0.00264*CONST_PI / (3600.0 * 180.0)*sin(omega)
                    + 0.000063*CONST_PI / (3600.0 * 180.0)*sin(2.0 *omega);
        }
        else
            gmstg = gmst;
        gmstg = fmod(gmstg, 2.0*CONST_PI);

        thetasa = 7.29211514670698e-05 * (1.0 - lod / 86400.0);
        omegaearth[0] = 0.0;
        omegaearth[1] = 0.0;
        omegaearth[2] = thetasa;

        st[0][0] = cos(gmstg);
        st[0][1] = -sin(gmstg);
        st[0][2] = 0.0;
        st[1][0] = sin(gmstg);
        st[1][1] = cos(gmstg);
        st[1][2] = 0.0;
        st[2][0] = 0.0;
        st[2][1] = 0.0;
        st[2][2] = 1.0;

        pm = polarm(xp, yp, julianCenturies, e80);

        rpef  = transpose(st)*rteme;
        recef = transpose(pm)*rpef;

        spef  = transpose(st) * steme;
        secef = transpose(pm) * spef;

        thetasa = 7.29211514670698e-05 * (1.0  - lod/86400.0 );
        omegaearth = vec3(0, 0, thetasa);

        vpef  = (transpose(st) * vteme) - cross(omegaearth, rpef);
        vecef = transpose(pm) * vpef;

        temp  = cross(omegaearth,rpef);

        aecef = transpose(pm)*(transpose(st)*ateme - cross(omegaearth,temp) - (2.0 * cross(omegaearth,vpef)));
        DCM_ET = transpose(pm) * st;
    }

    mat3 polarm(double xp, double yp, double ttt, eOpt opt) {
        double cosxp, cosyp, sinxp, sinyp, sp, cossp, sinsp;

        mat3 pm = mat3();

        cosxp = cos(xp);
        sinxp = sin(xp);
        cosyp = cos(yp);
        sinyp = sin(yp);

        if ((opt == e80) | (opt == e96))
        {
            pm[0][0] = cosxp;
            pm[0][1] = 0.0;
            pm[0][2] = -sinxp;
            pm[1][0] = sinxp * sinyp;
            pm[1][1] = cosyp;
            pm[1][2] = cosxp * sinyp;
            pm[2][0] = sinxp * cosyp;
            pm[2][1] = -sinyp;
            pm[2][2] = cosxp * cosyp;
        }
        else
        {
            // approximate sp value in rad
            sp = -47.0e-6 * ttt * CONST_PI / (180.0 * 3600.0);
            cossp = cos(sp);
            sinsp = sin(sp);

            // form the matrix
            pm[0][0] = cosxp * cossp;
            pm[0][1] = -cosyp * sinsp + sinyp * sinxp * cossp;
            pm[0][2] = -sinyp * sinsp - cosyp * sinxp * cossp;
            pm[1][0] = cosxp * sinsp;
            pm[1][1] = cosyp * cossp + sinyp * sinxp * sinsp;
            pm[1][2] = sinyp * cossp - cosyp * sinxp * sinsp;
            pm[2][0] = sinxp;
            pm[2][1] = -sinyp * cosxp;
            pm[2][2] = cosyp * cosxp;
        }

        return pm;
    }  //  polarm

    double gstime(double jdut1) {
        const double deg2rad = CONST_PI / 180.0;
        double       temp, tut1;

        tut1 = (jdut1 - 2451545.0) / 36525.0;
        temp = -6.2e-6* tut1 * tut1 * tut1 + 0.093104 * tut1 * tut1 +
               (876600.0 * 3600 + 8640184.812866) * tut1 + 67310.54841;  // sec
        temp = fmod(temp * deg2rad / 240.0, CONST_PI * 2.0f); //360/86400 = 1/240, to deg, to rad

        // ------------------------ check quadrants ---------------------
        if (temp < 0.0)
            temp = temp + (CONST_PI * 2.0f);

        return temp;
    }

    mat3 precess(double julianCenturies) {
        double convertToRad = CONST_PI / (180.0 * 3600.0);
        double julianCenturiesSquared = pow(julianCenturies, 2);
        double julianCenturiesCubed = pow(julianCenturies, 3);

        double psia  =             5038.7784*julianCenturies - 1.07259*julianCenturiesSquared - 0.001147*julianCenturiesCubed;
        double wa    = 84381.448                             + 0.05127*julianCenturiesSquared - 0.007726*julianCenturiesCubed;
        double ea    = 84381.448 -   46.8150*julianCenturies - 0.00059*julianCenturiesSquared + 0.001813*julianCenturiesCubed;
        double xa    =               10.5526*julianCenturies - 2.38064*julianCenturiesSquared - 0.001125*julianCenturiesCubed;
        double zeta  =             2306.2181*julianCenturies + 0.30188*julianCenturiesSquared + 0.017998*julianCenturiesCubed;
        double theta =             2004.3109*julianCenturies - 0.42665*julianCenturiesSquared - 0.041833*julianCenturiesCubed;
        double z     =             2306.2181*julianCenturies + 1.09468*julianCenturiesSquared + 0.018203*julianCenturiesCubed;

        psia  = psia  * convertToRad;
        wa    = wa    * convertToRad;
        ea    = ea    * convertToRad;
        xa    = xa    * convertToRad;
        zeta  = zeta  * convertToRad;
        theta = theta * convertToRad;
        z     = z     * convertToRad;

        double coszeta  = cos(zeta);
        double sinzeta  = sin(zeta);
        double costheta = cos(theta);
        double sintheta = sin(theta);
        double cosz     = cos(z);
        double sinz     = sin(z);

        double row1col1 = (coszeta * costheta * cosz) - (sinzeta * sinz);
        double row1col2 = (coszeta * costheta * sinz) + (sinzeta * cosz);
        double row1col3 =  coszeta * sintheta;
        double row2col1 = (-sinzeta * costheta * cosz) - (coszeta * sinz);
        double row2col2 = (-sinzeta * costheta * sinz) + (coszeta * cosz);
        double row2col3 = -sinzeta * sintheta;
        double row3col1 = -sintheta * cosz;
        double row3col2 = -sintheta * sinz;
        double row3col3 =  costheta;

        return mat3(row1col1, row2col1, row3col1, row1col2, row2col2, row3col2,row1col3, row2col3, row3col3);
    }

}
