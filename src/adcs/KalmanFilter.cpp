//
// Created by Charles on 4/9/2021.
//

#include "adcs/EKF.h"

namespace adcs {

    void ekf_init(vec7 &x_check, mat7 &P_check, vec3 S_E, vec3 B_E, vec3 S_B, vec3 B_B) {
        mat3 dcm_BE;
        //Initial state guess using Triad
        triad(dcm_BE,S_E,B_E,S_B,B_B);
        vec4 q_BE = DCM2Quat(dcm_BE);
        x_check = vec7(q_BE[0],q_BE[1],q_BE[2],q_BE[3],0,0,0);

        P_check = mat7 (1.0,0,0,0,0,0,0, //covariance,q1,(high,guess)
                   0,1.0,0,0,0,0,0, //covariance,q2
                   0,0,1.0,0,0,0,0, //covariance,q3
                   0,0,0,1.0,0,0,0, //covariance,q4
                   0,0,0,0,0.1,0,0, //covariance,wx
                   0,0,0,0,0,0.1,0, //covariance,wy
                   0,0,0,0,0,0,0.1); //covariance,wz)
    }

    void ekf_loop(float &x_check[7], mat7 &P_check, vec3 Se, vec3 Be, ){

        float q1 = x_check[0];
        float q2 = x_check[1];
        float q3 = x_check[2];
        float q4 = x_check[3];
        float wx = x_check[4];
        float wy = x_check[5];
        float wz = x_check[6];





    };

}