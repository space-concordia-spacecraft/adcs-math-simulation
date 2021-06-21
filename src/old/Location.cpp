//
// Created by Ruben on 2/12/2021.
//

#include "old/Location.h"

namespace adcs::location {

    // simple function to store help levels that can be set on/off during execution
    void sethelp(char& iauhelp, char iauopt)
    {
        static char iaustore;

        if (iauopt != ' ')
        {
            iauhelp = iauopt;
            iaustore = iauopt;
        }
        else
            iauhelp = iaustore;
    }

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

    void eci_teme(int ddpsi, int ddeps, vec3 reci, eOpt opt, double julianCenturies, vec3 &rteme){
        mat3 prec = precess(julianCenturies);

        iau80data iau;

        double deltapsi = 0, deltaeps = 0, trueeps = 0, meaneps = 0, omega = 0;
        mat3 nut;

        nutation(julianCenturies, ddpsi, ddeps,
                iau, opt,
                deltapsi, deltaeps, trueeps, meaneps, omega,
                nut);

        double eqeg = deltapsi * cos(meaneps);
        eqeg = fmod(eqeg, 2.0*CONST_PI);

        mat3 eqe;

        eqe[0][0] = cos(eqeg);
        eqe[0][1] = sin(eqeg);
        eqe[0][2] = 0.0;
        eqe[1][0] = -sin(eqeg);
        eqe[1][1] = cos(eqeg);
        eqe[1][2] = 0.0;
        eqe[2][0] = 0.0;
        eqe[2][1] = 0.0;
        eqe[2][2] = 1.0;

        mat3 tm = eqe * transpose(nut) * transpose(prec);

        rteme = tm * reci;
    }

    /* -----------------------------------------------------------------------------
    *
    *                           function nutation
    *
    *  this function calulates the transformation matrix that accounts for the
    *    effects of nutation.
    *
    *  author        : david vallado                  719-573-2600   27 jun 2002
    *
    *  revisions
    *    vallado     - consolidate with iau 2000                     14 feb 2005
    *    vallado     - conversion to c++                             21 feb 2005
    *    vallado     - conversion to c#                              16 Nov 2011
    *
    *  inputs          description                                 range / units
    *    ttt         - julian centuries of tt
    *    ddpsi       - delta psi correction to gcrf                      rad
    *    ddeps       - delta eps correction to gcrf                      rad
    *    iau80arr    - record containing the iau80 constants rad
    *    opt         - method option                               e00cio, e00a, e96, e80
    *
    *  outputs       :
    *    deltapsi    - nutation in longitude angle                       rad
    *    trueeps     - true obliquity of the ecliptic                    rad
    *    meaneps     - mean obliquity of the ecliptic                    rad
    *    raan        -                                                   rad
    *    nut         - transform matrix for tod - mod
    *
    *  locals        :
    *    iar80       - integers for fk5 1980
    *    rar80       - reals for fk5 1980                                rad
    *    l           -                                                   rad
    *    ll          -                                                   rad
    *    f           -                                                   rad
    *    d           -                                                   rad
    *    deltaeps    - change in obliquity                               rad
    *
    *  coupling      :
    *    fundarg     - find fundamental arguments
    *    fmod      - modulus division
    *
    *  references    :
    *    vallado       2013, 213, 224
    * --------------------------------------------------------------------------- */
    void nutation
            (
                    double ttt, double ddpsi, double ddeps,
                    const iau80data &iau80arr, eOpt opt,
                    double& deltapsi, double& deltaeps, double& trueeps, double& meaneps, double& omega,
                    mat3 &nut
            )
    {
        // locals
        double deg2rad, l, l1, f, d,
                lonmer, lonven, lonear, lonmar, lonjup, lonsat, lonurn, lonnep, precrate,
                cospsi, sinpsi, coseps, sineps, costrueeps, sintrueeps;
        int  i;
        double tempval;

        char iauhelp;
        sethelp(iauhelp, ' ');

        deg2rad = CONST_PI / 180.0;

        // ---- determine coefficients for iau 1980 nutation theory ----
        meaneps = ((0.001813  * ttt - 0.00059) * ttt - 46.8150) * ttt + 84381.448;
        meaneps = fmod(meaneps / 3600.0, 360.0);
        meaneps = meaneps * deg2rad;

        fundarg(ttt, opt, l, l1, f, d, omega,
                lonmer, lonven, lonear, lonmar, lonjup, lonsat, lonurn, lonnep, precrate);

        deltapsi = 0.0;
        deltaeps = 0.0;
        for (i = 105; i >= 0; i--)
        {
            tempval = iau80arr.iar80[i][0] * l + iau80arr.iar80[i][1] * l1 + iau80arr.iar80[i][2] * f +
                      iau80arr.iar80[i][3] * d + iau80arr.iar80[i][4] * omega;
            deltapsi = deltapsi + (iau80arr.rar80[i][0] + iau80arr.rar80[i][1] * ttt)  *  sin(tempval);
            deltaeps = deltaeps + (iau80arr.rar80[i][2] + iau80arr.rar80[i][3] * ttt) * cos(tempval);
        }

        // --------------- find nutation parameters --------------------
        deltapsi = fmod(deltapsi + ddpsi, 2.0 * CONST_PI);
        deltaeps = fmod(deltaeps + ddeps, 2.0 * CONST_PI);

        trueeps = meaneps + deltaeps;

        cospsi = cos(deltapsi);
        sinpsi = sin(deltapsi);
        coseps = cos(meaneps);
        sineps = sin(meaneps);
        costrueeps = cos(trueeps);
        sintrueeps = sin(trueeps);

        nut[0][0] = cospsi;
        nut[0][1] = costrueeps * sinpsi;
        nut[0][2] = sintrueeps * sinpsi;
        nut[1][0] = -coseps * sinpsi;
        nut[1][1] = costrueeps * coseps * cospsi + sintrueeps * sineps;
        nut[1][2] = sintrueeps * coseps * cospsi - sineps * costrueeps;
        nut[2][0] = -sineps * sinpsi;
        nut[2][1] = costrueeps * sineps * cospsi - sintrueeps * coseps;
        nut[2][2] = sintrueeps * sineps * cospsi + costrueeps * coseps;

        // alternate approach
        //MathTimeLib::rot1mat(trueeps, n1);
        //MathTimeLib::rot3mat(deltapsi, n2);
        //MathTimeLib::rot1mat(-meaneps, n3);
        //MathTimeLib::matmult(n2, n1, tr1, 3, 3, 3);
        //MathTimeLib::matmult(n3, tr1, nut, 3, 3, 3);

        if (iauhelp == 'y')
            printf("meaneps %11.7f dp  %11.7f de  %11.7f te  %11.7f  \n", meaneps * 180 / CONST_PI, deltapsi * 180 / CONST_PI,
                   deltaeps * 180 / CONST_PI, trueeps * 180 / CONST_PI);
    }  //  nutation

    /* -----------------------------------------------------------------------------
         *
         *                           function fundarg
         *
         *  this function calulates the delauany variables and planetary values for
         *  several theories.
         *
         *  author        : david vallado                  719-573-2600   16 jul 2004
         *
         *  revisions
         *    vallado     - conversion to c++                             23 nov 2005
         *    vallado     - conversion to c#                              16 Nov 2011
         *
         *  inputs          description                                  range / units
         *    ttt         - julian centuries of tt
         *    opt         - method option                                e00cio, e00a, e96, e80
         *
         *  outputs       :
         *    l           - mean anomaly of the moon                          rad
         *    l1          - mean anomaly of the Sun                           rad
         *    f           - mean longitude of the Moon minus that of asc node rad
         *    d           - mean elongation of the Moon from the Sun          rad
         *    omega       - mean longitude of the ascending node of the Moon  rad
         *    planetary longitudes                                          rad
         *
         *  locals        :
         *
         *  coupling      :
         *    none        -
         *
         *  references    :
         *    vallado       2013, 210-211, 225
         * --------------------------------------------------------------------------- */

    void fundarg
            (
                    double ttt, eOpt opt,
                    double& l, double& l1, double& f, double& d, double& omega,
                    double& lonmer, double& lonven, double& lonear, double& lonmar,
                    double& lonjup, double& lonsat, double& lonurn, double& lonnep,
                    double& precrate
            )
    {
        double deg2rad, oo3600;
        char iauhelp;

        sethelp(iauhelp, ' ');
        deg2rad = CONST_PI / 180.0;
        oo3600 = 1.0 / 3600.0;
        l = l1 = f = d = omega = lonmer = lonven = lonear = lonmar = lonjup = lonsat = lonurn = lonnep = precrate = 0.0;

        // ---- determine coefficients for various iers nutation theories ----
        // ----  iau-2010 cio theory and iau-2000a theory
        if (opt == e00cio || opt == e00a)
        {
            // ------ form the delaunay fundamental arguments in ", converted to rad
            l = ((((-0.00024470 * ttt + 0.051635) * ttt + 31.8792) * ttt + 1717915923.2178) * ttt + 485868.249036) * oo3600;
            l1 = ((((-0.00001149 * ttt + 0.000136) * ttt - 0.5532) * ttt + 129596581.0481) * ttt + 1287104.793048) * oo3600;
            f = ((((+0.00000417 * ttt - 0.001037) * ttt - 12.7512) * ttt + 1739527262.8478) * ttt + 335779.526232) * oo3600;
            d = ((((-0.00003169 * ttt + 0.006593) * ttt - 6.3706) * ttt + 1602961601.2090) * ttt + 1072260.703692) * oo3600;
            omega = ((((-0.00005939 * ttt + 0.007702) * ttt + 7.4722) * ttt - 6962890.5431) * ttt + 450160.398036) * oo3600;

            // ------ form the planetary arguments in ", converted to rad
            lonmer = (908103.259872 + 538101628.688982  * ttt) * oo3600;
            lonven = (655127.283060 + 210664136.433548  * ttt) * oo3600;
            lonear = (361679.244588 + 129597742.283429  * ttt) * oo3600;
            lonmar = (1279558.798488 + 68905077.493988  * ttt) * oo3600;
            lonjup = (123665.467464 + 10925660.377991  * ttt) * oo3600;
            lonsat = (180278.799480 + 4399609.855732  * ttt) * oo3600;
            lonurn = (1130598.018396 + 1542481.193933  * ttt) * oo3600;
            lonnep = (1095655.195728 + 786550.320744  * ttt) * oo3600;
            precrate = ((1.112022 * ttt + 5028.8200) * ttt) * oo3600;
            // these are close (all in rad) - usually 1e-10, but some are as high as 1e-06
            //lonmer = (4.402608842 + 2608.7903141574 * ttt) % twopi;
            //lonven = (3.176146697 + 1021.3285546211 * ttt) % twopi;
            //lonear = (1.753470314 + 628.3075849991 * ttt) % twopi;
            //lonmar = (6.203480913 + 334.0612426700 * ttt) % twopi;
            //lonjup = (0.599546497 + 52.9690962641 * ttt) % twopi;
            //lonsat = (0.874016757 + 21.3299104960 * ttt) % twopi;
            //lonurn = (5.481293872 + 7.4781598567 * ttt) % twopi;
            //lonnep = (5.311886287 + 3.8133035638 * ttt) % twopi;
            //precrate = (0.024381750 + 0.00000538691 * ttt ) *ttt;
        }

        // ---- iau-2000b theory
        if (opt == e00b)
        {
            // ------ form the delaunay fundamental arguments in deg
            l = (1717915923.2178  * ttt + 485868.249036) * oo3600;
            l1 = (129596581.0481  * ttt + 1287104.79305) * oo3600;
            f = (1739527262.8478  * ttt + 335779.526232) * oo3600;
            d = (1602961601.2090  * ttt + 1072260.70369) * oo3600;
            omega = (-6962890.5431  * ttt + 450160.398036) * oo3600;

            // ------ form the planetary arguments in deg
            lonmer = 0.0;
            lonven = 0.0;
            lonear = 0.0;
            lonmar = 0.0;
            lonjup = 0.0;
            lonsat = 0.0;
            lonurn = 0.0;
            lonnep = 0.0;
            precrate = 0.0;
            // instead uses a constant rate
            // dplan = -0.135 * oo3600 * deg2rad;
            // deplan = 0.388 * oo3600 * deg2rad;
        }

        // ---- iau-1996 theory
        if (opt == e96)
        {
            // ------ form the delaunay fundamental arguments in deg
            l = ((((-0.00024470 * ttt + 0.051635) * ttt + 31.8792) * ttt + 1717915923.2178) * ttt) * oo3600 + 134.96340251;
            l1 = ((((-0.00001149 * ttt - 0.000136) * ttt - 0.5532) * ttt + 129596581.0481) * ttt) * oo3600 + 357.52910918;
            f = ((((+0.00000417 * ttt + 0.001037) * ttt - 12.7512) * ttt + 1739527262.8478) * ttt) * oo3600 + 93.27209062;
            d = ((((-0.00003169 * ttt + 0.006593) * ttt - 6.3706) * ttt + 1602961601.2090) * ttt) * oo3600 + 297.85019547;
            omega = ((((-0.00005939 * ttt + 0.007702) * ttt + 7.4722) * ttt - 6962890.2665) * ttt) * oo3600 + 125.04455501;
            // ------ form the planetary arguments in deg
            lonmer = 0.0;
            lonven = 181.979800853 + 58517.8156748   * ttt;
            lonear = 100.466448494 + 35999.3728521   * ttt;
            lonmar = 355.433274605 + 19140.299314    * ttt;
            lonjup = 34.351483900 + 3034.90567464  * ttt;
            lonsat = 50.0774713998 + 1222.11379404  * ttt;
            lonurn = 0.0;
            lonnep = 0.0;
            precrate = (0.0003086 * ttt + 1.39697137214) * ttt;
        }

        // ---- iau-1980 theory
        if (opt == e80)
        {
            // ------ form the delaunay fundamental arguments in deg
            l = ((((0.064) * ttt + 31.310) * ttt + 1717915922.6330) * ttt) * oo3600 + 134.96298139;
            l1 = ((((-0.012) * ttt - 0.577) * ttt + 129596581.2240) * ttt) * oo3600 + 357.52772333;
            f = ((((0.011) * ttt - 13.257) * ttt + 1739527263.1370) * ttt) * oo3600 + 93.27191028;
            d = ((((0.019) * ttt - 6.891) * ttt + 1602961601.3280) * ttt) * oo3600 + 297.85036306;
            omega = ((((0.008) * ttt + 7.455) * ttt - 6962890.5390) * ttt) * oo3600 + 125.04452222;
            // ------ form the planetary arguments in deg
            // iers tn13 shows no planetary
            // seidelmann shows these equations
            // circ 163 shows no planetary
            // ???????
            lonmer = 252.3 + 149472.0  * ttt;
            lonven = 179.9 + 58517.8  * ttt;
            lonear = 98.4 + 35999.4  * ttt;
            lonmar = 353.3 + 19140.3  * ttt;
            lonjup = 32.3 + 3034.9  * ttt;
            lonsat = 48.0 + 1222.1  * ttt;
            lonurn = 0.0;
            lonnep = 0.0;
            precrate = 0.0;
        }

        // ---- convert units from deg to rad
        l = fmod(l, 360.0)      *  deg2rad;
        l1 = fmod(l1, 360.0)     *  deg2rad;
        f = fmod(f, 360.0)      *  deg2rad;
        d = fmod(d, 360.0)      *  deg2rad;
        omega = fmod(omega, 360.0)  *  deg2rad;

        lonmer = fmod(lonmer, 360.0) * deg2rad;
        lonven = fmod(lonven, 360.0) * deg2rad;
        lonear = fmod(lonear, 360.0) * deg2rad;
        lonmar = fmod(lonmar, 360.0) * deg2rad;
        lonjup = fmod(lonjup, 360.0) * deg2rad;
        lonsat = fmod(lonsat, 360.0) * deg2rad;
        lonurn = fmod(lonurn, 360.0) * deg2rad;
        lonnep = fmod(lonnep, 360.0) * deg2rad;
        precrate = fmod(precrate, 360.0) * deg2rad;

        if (iauhelp == 'y')
        {
            printf("fa %11.7f  %11.7f  %11.7f  %11.7f  %11.7f deg \n", l * 180 / CONST_PI, l1 * 180 / CONST_PI, f * 180 / CONST_PI, d * 180 / CONST_PI, omega * 180 / CONST_PI);
            printf("fa %11.7f  %11.7f  %11.7f  %11.7f deg \n", lonmer * 180 / CONST_PI, lonven * 180 / CONST_PI, lonear * 180 / CONST_PI, lonmar * 180 / CONST_PI);
            printf("fa %11.7f  %11.7f  %11.7f  %11.7f deg \n", lonjup * 180 / CONST_PI, lonsat * 180 / CONST_PI, lonurn * 180 / CONST_PI, lonnep * 180 / CONST_PI);
            printf("fa %11.7f  \n", precrate * 180 / CONST_PI);
        }
    }  // procedure fundarg

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

    void igrfs(double latitude, double longitude, double altitude, vec3 &magneticField) {
        double costheta = cos(((CONST_PI / 2.0)- latitude));
        double sintheta = sin(((CONST_PI / 2.0)- latitude));

        double r = altitude;
        double phi = longitude;

        double gh [195] = {-29442, -1501, 4797.1, -2445.1, 3012.9, -2845.6, 1676.7, -641.9, 1350.7, -2352.3, -115.3, 1225.6, 244.9, 582, -538.4, 907.6, 813.7, 283.3, 120.4, -188.7, -334.9, 180.9, 70.4, -329.5, -232.6, 360.1, 47.3, 192.4, 197, -140.9, -119.3, -157.5, 16, 4.1, 100.2, 70, 67.7, -20.8, 72.7, 33.2, -129.9, 58.9, -28.9, -66.7, 13.2, 7.3, -70.9, 62.6, 81.6, -76.1, -54.1, -6.8, -19.5, 51.8, 5.7, 15, 24.4, 9.4, 3.4, -2.8, -27.4, 6.8, -2.2, 24.2, 8.8, 10.1, -16.9, -18.3, -3.2, 13.3, -20.6, -14.6, 13.4, 16.2, 11.7, 5.7, -15.9, -9.1, -2, 2.1, 5.4, 8.8, -21.6, 3.1, 10.8, -3.3, 11.8, 0.7, -6.8, -13.3, -6.9, -0.1, 7.8, 8.7, 1, -9.1, -4, -10.5, 8.4, -1.9, -6.3, 3.2, 0.1, -0.4, 0.5, 4.6, -0.5, 4.4, 1.8, -7.9, -0.7, -0.6, 2.1, -4.2, 2.4, -2.8, -1.8, -1.2, -3.6, -8.7, 3.1, -1.5, -0.1, -2.3, 2, 2, -0.7, -0.8, -1.1, 0.6, 0.8, -0.7, -0.2, 0.2, -2.2, 1.7, -1.4, -0.2, -2.5, 0.4, -2, 3.5, -2.4, -1.9, -0.2, -1.1, 0.4, 0.4, 1.2, 1.9, -0.8, -2.2, 0.9, 0.3, 0.1, 0.7, 0.5, -0.1, -0.3, 0.3, -0.4, 0.2, 0.2, -0.9, -0.9, -0.1, 0, 0.7, 0, -0.9, -0.9, 0.4, 0.4, 0.5, 1.6, -0.5, -0.5, 1, -1.2, -0.2, -0.1, 0.8, 0.4, -0.1, -0.1, 0.3, 0.4, 0.1, 0.5, 0.5, -0.3, -0.4, -0.4, -0.3, -0.8};

        int nmax = 13;
      
        float cosphi[nmax + 1];
        float sinphi[nmax + 1];

        for (int i = 1; i <= nmax; i++) {
            cosphi[i] = cos(i * phi);
            sinphi[i] = sin(i * phi);
        }


        int Pmax = (nmax + 1) * (nmax + 2) / 2;

        double Br = 0; 
        double Bt = 0; 
        double Bp = 0;

        double P[Pmax + 1];

        P[1] = 1;  
        P[3] = sintheta;

        double dP[Pmax + 1];

        dP[1] = 0; 
        dP[3] = costheta;


        int m = 1;
        int n = 0;
        int coefindex = 1;

        double a_r = pow((CONST_EARTH_RADIUS / r), 2);

        for (int i = 2; i <= Pmax; i++) {
            if (n < m) {
                m = 0;
                n++;
                a_r = a_r * (CONST_EARTH_RADIUS / r);
            }
            if (m < n && i != 3) {
                int last1n = i - n;
                int last2n = i - 2 * n + 1;
                // do magn field
                P[i] = (2 * n - 1) / sqrt(pow(n, 2) - pow(m, 2)) * costheta * P[last1n] -  sqrt((pow((n - 1), 2) - pow(m, 2)) / (pow(n, 2) - pow(m, 2))) * P[last2n];
                dP[i] = (2 * n - 1) / sqrt(pow(n, 2) - pow(m, 2)) * (costheta * dP[last1n] -
                    sintheta * P[last1n]) - sqrt((pow((n - 1), 2) - pow(m, 2)) / (pow(n, 2) - pow(m, 2))) *
                    dP[last2n];
            }
            else if(i != 3) {
                int lastn = i - n - 1;
                P[i] = sqrt(1 - 1 / (2 * m)) * sintheta * P[lastn];
                dP[i] = sqrt(1 - 1 / (2 * m)) * (sintheta * dP[lastn] + costheta * P[lastn]);
            }
            if (m == 0) {
                double coef = a_r * gh[coefindex];
                Br = Br + (n + 1) * coef * P[i];
                Bt = Bt - coef * dP[i];
                coefindex++;
            }
            else {
                double coef = a_r * (gh[coefindex] * cosphi[m] + gh[coefindex + 1] * sinphi[m]);
                Br = Br + (n + 1) * coef * P[i];
                Bt = Bt - coef * dP[i];

                if (sintheta == 0) { 
                        Bp = Bp - costheta * a_r * (-gh[coefindex] * sinphi[m] + gh[coefindex + 1] * cosphi[m]) * dP[i];
                }
                else {
                    Bp = Bp - 1 / sintheta * a_r * m * (-gh[coefindex] * sinphi[m] + 
                        gh[coefindex + 1] * cosphi[m]) * P[i];
                }
                    coefindex = coefindex + 2; 
            }
               
            m++;

        }

        //Bn
        magneticField[0] = -Bt;
        //Be
        magneticField[1] = Bp;
        //Bd
        magneticField[2] = Br;

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
        vec3 magneticField = glm::cross(dipoleMoment, (b * 1e-9));

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

        rpef  = transpose(st) * rteme;
        recef = transpose(pm) * rpef;

        spef  = transpose(st) * steme;
        secef = transpose(pm) * spef;

        thetasa = 7.29211514670698e-05 * (1.0  - lod/86400.0 );
        omegaearth = vec3(0, 0, thetasa);

        vpef  = (transpose(st) * vteme) - cross(omegaearth, rpef);
        vecef = transpose(pm) * vpef;

        temp  = cross(omegaearth,rpef);

        aecef = transpose(pm)*(transpose(st)*ateme - cross(omegaearth,temp) - (2.0f * cross(omegaearth,vpef)));
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

    void get_sun_in_teme(double jdtdb, double jdtdbF, vec3 &rteme) {
        vec3 rsun(0, 0, 0), reci(0,0,0);
        double rtasc, decl;

        // Julian Centuries of Terrestrial time
        double ttt = (jdtdb + jdtdbF - 2451545.0) / 36525.0;

        sunalmanac(jdtdb, jdtdbF, rsun, rtasc, decl);
        mod_eci(rsun, ttt, reci);
        eci_teme(0, 0, reci, e80, ttt, rteme);
    }

    void get_igrf(vec3 recef, double & height, double & latitude, double & longitude, vec3 & magneticField) {
        recef *= 1000;
        vec3 position;

        double altitude = 0;

        xyz_ell3(recef, latitude, longitude, altitude, height);
        igrfs(latitude, longitude, altitude/1000.0, position);
        lg2ct(position, latitude, longitude, magneticField);

        magneticField *= 1e-9;
        height /= 1000;
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
