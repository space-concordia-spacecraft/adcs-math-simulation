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

            char longstr1[130] = {'1',' ','4','4','3','3','2','U',' ','9','8','0','6','7','Q','H',' ',' ','1','9','3','5','0','.','7','7','7','2','1','4','6','8',' ',' ','.','0','0','0','0','6','2','7','4',' ',' ','0','0','0','0','0','-','0',' ',' ','1','0','0','5','4','-','3',' ','0',' ',' ','9','9','9','8'},
            longstr2[130] = "2 44332  51.6386 172.4798 0005656  48.9347 311.2132 15.54514188 2835547";

            double startmfe, stopmfe, deltamin, opsmode;
            elsetrec satrec;

            // TLE
            SGP4Funcs::twoline2rv(longstr1, longstr2, 'v', 'm', 'i', gravconsttype::wgs84, startmfe, stopmfe, deltamin, satrec);

            // Get Julian Date
            double jd = 0, jdFrac = 0;
            SGP4Funcs::jday_SGP4(0, 0, 0, 0, 0, 0, jd, jdFrac);

            // SGP4 init
            double r[3], v[3];
            SGP4Funcs::sgp4(satrec, jd, r, v);

            // Sun Prediction
            AstroLib::sun(0, 0, sunPosition, rtasc, decl);

            //mod2eci
            //eci2teme

            //teme2ecef
            AstroLib::teme_ecef(rteme, vteme, ateme, direction, recef, vecef, aecef, ttt, jdut, lod, xp, yp, eqeterms);

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