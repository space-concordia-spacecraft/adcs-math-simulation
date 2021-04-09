#include "adcs/ADCS.h"

namespace adcs {
    ADCS::ADCS(Simulation *sim):simulation(sim){
    }

    ADCS::~ADCS(){

    }

    void ADCS::run() {

        while(true){
            double sunPosition [3] = {0,0,0}, rteme[3] = {0,0,0}, vteme[3] = {0,0,0}, ateme[3] = {0,0,0};
            double recef[3] = {0,0,0}, vecef[3] = {0,0,0}, aecef[3] = {0,0,0};
            double rtasc, decl;

            char * longstr1 =  "1 44332U 98067QH  19350.77721468  .00006274  00000-0  10054-3 0  9998",
            * longstr2 = "2 44332  51.6386 172.4798 0005656  48.9347 311.2132 15.54514188 2835547";

            double startmfe, stopmfe, deltamin, opsmode;
            elsetrec satrec;

            // TLE
            SGP4Funcs::twoline2rv(longstr1, longstr2, 'v', 'm', 'i', gravconsttype::wgs84, startmfe, stopmfe, deltamin, satrec);

            // Get Julian Date
            double jd = 0, jdFrac = 0;
            time_t now = time(0);
            tm * gmtm = gmtime(&now);

            SGP4Funcs::jday_SGP4(gmtm->tm_year, gmtm->tm_mon, gmtm->tm_mday, gmtm->tm_hour, gmtm->tm_min, gmtm->tm_sec, jd, jdFrac);

            double ttt = (jd-2451545)/36525.0; // julian centuries

            // SGP4 init
            double r[3], v[3];
            SGP4Funcs::sgp4(satrec, jd, r, v);

            // Sun Prediction
            double reci[3] = {0,0,0};
            AstroLib::sun(0, 0, sunPosition, rtasc, decl); //sunalmanac
            //eci2teme

            //teme2ecef


            //xyz2ell3
            //igrf
            //lg2ct

            //itrf2body

            //disturbances torques
            //S/C dynamics


        }
    }

    void ADCS::setTLEs(char *longstr1, char *longstr2) {

    }
}