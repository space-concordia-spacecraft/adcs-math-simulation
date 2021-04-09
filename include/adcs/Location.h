#pragma once

#include "adcs/Constants.h"
#include "glm/glm.hpp"

using glm::mat3;
using glm::vec3;

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
    void sunalmanac(double julianDay, vec3 rsun);
    void mod_eci(vec3 rsun, double julianCenturies, vec3 reci);
    void eci_teme(int ddpsi, int ddeps, vec3 reci, double nut80, double ttt, vec3 rteme);

    double gstime(double julianDay);
    mat3 precess(double julianCenturies);
    void nutation(double julianCenturies, int ddpsi, int ddeps, double nut80);
    void fundarg(double ttt, eOpt opt,
                 double& l, double& l1, double& f, double& d, double& omega,
                 double& lonmer, double& lonven, double& lonear, double& lonmar,
                 double& lonjup, double& lonsat, double& lonurn, double& lonnep,
                 double& precrate);
    void iau80in();
    mat3 polarm(double xp, double yp, double ttt, eOpt opt);

    void teme_ecef(vec3 steme, vec3 rteme, vec3 vteme, vec3 ateme,
                   double julianCenturies, double jdut1,
                   vec3 &secef, vec3 &recef, vec3 &vecef, vec3 &aecef, mat3 &DCM_ET,
                   double lod, double xp, double yp, int eqeterms);

    void xyz_ell3(vec3 position, double &latitude, double &longitude, double &altitude, double &h);
    void igrfs(double latitude, double longitude, double altitude, vec3 &position);
    void lg2ct(vec3 position, double latitude, double longitude, vec3 &coordinateDifferences);

    void itrf_body(vec3 be, vec3 ve, vec3 p3, vec3 se, vec3 dcm_be, vec3 &b, vec3 &v, vec3 &p, vec3 &s);

    void disturbance_torque(vec3 dipoleMoment, vec3 b, vec3 p, vec3 inertiaMatrix, vec3 s, vec3 v, double h, vec3 &torque);

//    vec3 teme2ecef(double[3] steme, double[3] rteme, vec3 vteme, vec3 ateme, int julianCenturies, int julianDate, int lod, double xp, double yp, int eqeterms);
//    void itrf2body(double[3] b, double[3] vecef, vec3 recef, vec3 secef);



}