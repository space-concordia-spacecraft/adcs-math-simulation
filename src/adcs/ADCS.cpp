#include "adcs/ADCS.h"

namespace adcs {

    ADCS::ADCS(Simulation *sim):simulation(sim){
    }

    ADCS::~ADCS(){

    }

    void ADCS::run() {

        while(true){
            vec3 steme, rteme, vteme;
            vec3 secef, recef, vecef, aecef;
            vec3 b, v, p, s;
            mat3 dcm_et;
            vec3 ateme(1,1,1);

            vec3 be;

            char * longstr1 =  "1 44332U 98067QH  19350.77721468  .00006274  00000-0  10054-3 0  9998",
            * longstr2 = "2 44332  51.6386 172.4798 0005656  48.9347 311.2132 15.54514188 2835547";

            double startmfe, stopmfe, deltamin, opsmode;
            double height, latitude, longitude;
            elsetrec satrec;

            // TLE
            sgp::twoline2rv(longstr1, longstr2, 'v', 'm', 'i', static_cast<sgp::gravconsttype>(gravconsttype::wgs84), startmfe, stopmfe, deltamin, satrec);

            // Get Julian Date
            double jd = 0, jdFrac = 0;
            time_t now = time(0);
            tm * gmtm = gmtime(&now);

            sgp::jday_SGP4(gmtm->tm_year, gmtm->tm_mon, gmtm->tm_mday, gmtm->tm_hour, gmtm->tm_min, gmtm->tm_sec, jd, jdFrac);

            double ttt = (jd-2451545)/36525.0; // julian centuries

            // SGP4 init
            sgp::sgp4(satrec, jd, rteme, vteme);

            // Sun Prediction

            location::get_sun_in_teme(jd, jdFrac, steme);

            //teme2ecef
            location::teme_ecef(steme, rteme, vteme, ateme,
                                ttt, jd,
                                secef, recef, vecef, aecef, dcm_et,
                                0, (0.127631*CONST_PI/3600/180), (0.247746*CONST_PI/3600/180), 2);

            //igrf
            location::get_igrf(recef, height, latitude, longitude, be);

            //itrf2body
            location::itrf_body(be, vecef, recef, secef, dcm_be, b, v, p, s);

            //disturbances torques
            

            //S/C dynamics


        }
    }

    void ADCS::setTLEs(char *longstr1, char *longstr2) {

    }
}