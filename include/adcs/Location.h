#pragma once

#include "adcs/Constants.h"
#include "glm/glm.hpp"

using glm::dmat3;
using glm::dvec3;

namespace adcs::location {

    typedef enum
    {
        e80,
        e96,
        e00a,
        e00b,
        e00cio
    } eOpt;

    // Sun prediction
    void sunalmanac(double julianDay, dvec3 rsun);
    void mod_eci(dvec3 rsun, double julianCenturies, dvec3 reci);
    void eci_teme(int ddpsi, int ddeps, dvec3 reci, double nut80, double ttt, dvec3 rteme);

    double gstime(double julianDay);
    dmat3 precess(double julianCenturies);
    void nutation(double julianCenturies, int ddpsi, int ddeps, double nut80);
    void fundarg(double ttt, eOpt opt,
                 double& l, double& l1, double& f, double& d, double& omega,
                 double& lonmer, double& lonven, double& lonear, double& lonmar,
                 double& lonjup, double& lonsat, double& lonurn, double& lonnep,
                 double& precrate);
    void iau80in();
    dmat3 polarm(double xp, double yp, double ttt, eOpt opt);

    void teme_ecef(dvec3 steme, dvec3 rteme, dvec3 vteme, dvec3 ateme,
                   double julianCenturies, double jdut1,
                   dvec3 &secef, dvec3 &recef, dvec3 &vecef, dvec3 &aecef, dmat3 &DCM_ET,
                   double lod, double xp, double yp, int eqeterms);

    void xyz_ell3(dvec3 position, double &latitude, double &longitude, double &altitude, double &h);
    void igrfs(double latitude, double longitude, double altitude, dvec3 &position);
    void lg2ct(dvec3 position, double latitude, double longitude, dvec3 &coordinateDifferences);

    void itrf_body(dvec3 be, dvec3 ve, dvec3 p3, dvec3 se, dvec3 dcm_be, dvec3 &b, dvec3 &v, dvec3 &p, dvec3 &s);

    void disturbance_torque(dvec3 dipoleMoment, dvec3 b, dvec3 p, dvec3 inertiaMatrix, dvec3 s, dvec3 v, double h, dvec3 &torque);

//    vec3 teme2ecef(double[3] steme, double[3] rteme, vec3 vteme, vec3 ateme, int julianCenturies, int julianDate, int lod, double xp, double yp, int eqeterms);
//    void itrf2body(double[3] b, double[3] vecef, vec3 recef, vec3 secef);



}