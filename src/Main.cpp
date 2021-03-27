#include <iostream>
#include <memory>

#include "matplotlibcpp.h"
#include "open3d/Open3D.h"
#include "Constants.h"
#include "AstroLib.h"
#include "DTM_12.h"
#include "EopSpw.h"
#include "MathtIMElIB.h"
#include "MSIS_Vers.h"
#include "SGP4.h"
#include "SGP4DC.h"

namespace plt = matplotlibcpp;

using namespace open3d;

int main(int argc, char *argv[]) {
    plt::plot({1,3,2,4});
    plt::show();

//    utility::SetVerbosityLevel(utility::VerbosityLevel::Debug);
//    if (argc < 3) {
//        utility::LogInfo("Open3D {}\n", OPEN3D_VERSION);
//        utility::LogInfo("\n");
//        utility::LogInfo("Usage:\n");
//        utility::LogInfo("    > TestVisualizer [mesh|pointcloud] [filename]\n");
//        // CI will execute this file without input files, return 0 to pass
//        return 0;
//    }
//    std::string option(argv[1]);
//    if (option == "mesh") {
//        auto mesh_ptr = std::make_shared<geometry::TriangleMesh>();
//        if (io::ReadTriangleMesh(argv[2], *mesh_ptr)) {
//            utility::LogInfo("Successfully read {}\n", argv[2]);
//        } else {
//            utility::LogWarning("Failed to read {}\n\n", argv[2]);
//            return 1;
//        }
//        mesh_ptr->ComputeVertexNormals();
//        visualization::DrawGeometries({mesh_ptr}, "Mesh", 1600, 900);
//
//    } else if (option == "pointcloud") {
//        auto cloud_ptr = std::make_shared<geometry::PointCloud>();
//        if (io::ReadPointCloud(argv[2], *cloud_ptr)) {
//            utility::LogInfo("Successfully read {}\n", argv[2]);
//        } else {
//            utility::LogWarning("Failed to read {}\n\n", argv[2]);
//            return 1;
//        }
//        cloud_ptr->NormalizeNormals();
//        visualization::DrawGeometries({cloud_ptr}, "PointCloud", 1600, 900);
//    } else {
//        utility::LogWarning("Unrecognized option: {}\n", option);
//        return 1;
//    }
//    utility::LogInfo("End of the test.\n");

    while(true){
        double sunPosition [3] = {0,0,0}, rteme[3] = {0,0,0}, vteme[3] = {0,0,0}, ateme[3] = {0,0,0};
        double recef[3] = {0,0,0}, vecef[3] = {0,0,0}, aecef[3] = {0,0,0};
        double rtasc, decl;

        char longstr1[130], longstr2[130];
        char typerun = 'v', typeinput = 'm';

        double startmfe, stopmfe, deltamin, opsmode;
        gravconsttype whichconst;
        elsetrec satrec;

        // TLE
        SGP4Funcs::twoline2rv(longstr1, longstr2, typerun, typeinput, opsmode, whichconst, startmfe, stopmfe, deltamin, satrec);

        // Get Julian Date
        double jd = 0, jdFrac = 0;
        SGP4Funcs::jday_SGP4(0, 0, 0, 0, 0, 0, jd, jdfrac);

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

    return 0;
}

