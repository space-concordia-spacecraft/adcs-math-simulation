//
// Created by Charles on 4/9/2021.
//

#include "adcs/EKF.h"


namespace adcs {

    mat7 K;
    mat6 H;
    mat36 HE;

    float q1;
    float q2;
    float q3;
    float q4;
    float wx;
    float wy;
    float wz;

    float hwx;
    float hwy;
    float hwz;


    void ekf_init(vec7 &x_check, mat7 &P_check, vec3 S_E, vec3 B_E, vec3 S_B, vec3 B_B) {
        mat3 dcm_BE;
        //Initial state guess using Triad
        triad(dcm_BE,S_E,B_E,S_B,B_B);
        vec4 q_BE = DCM2quat(dcm_BE);
        x_check = vec7(q_BE[0],q_BE[1],q_BE[2],q_BE[3],0,0,0);

        P_check = mat7(1.0,0,0,0,0,0,0, //covariance,q1,(high,guess)
                   0,1.0,0,0,0,0,0, //covariance,q2
                   0,0,1.0,0,0,0,0, //covariance,q3
                   0,0,0,1.0,0,0,0, //covariance,q4
                   0,0,0,0,0.1,0,0, //covariance,wx
                   0,0,0,0,0,0.1,0, //covariance,wy
                   0,0,0,0,0,0,0.1); //covariance,wz)
    }

    void ekf_loop(vec7 &x_check, mat7 &P_check, vec3 S_E, vec3 B_E,vec3 S_B,vec3 B_B,vec3 u, mat3 I_inv, mat3 I,bool eclipse,vec3 Lw,float step){

        //Splitting variables
         q1 = x_check[0];
         q2 = x_check[1];
         q3 = x_check[2];
         q4 = x_check[3];
         wx = x_check[4];
         wy = x_check[5];
         wz = x_check[6];

         hwx = Lw[0];
         hwy = Lw[1];
         hwz = Lw[2];

        //**************************************Prediction**********************************************************************
        // Jacobian F
        mat67 F = mat67(1,0.5 * step * wz,  -0.5 * step * wy,  0.5 * step * wx,   0.5 * step * q4,-0.5 * step * q3, 0.5 * step * q2,
                         -0.5 * step * wz,1, 0.5 * step * wx,  0.5 * step * wy,   0.5 * step * q3, 0.5 * step * q4,-0.5 * step * q1,
                          0.5 * step * wy,  -0.5 * step * wx,1,0.5 * step * wz,  -0.5 * step * q2, 0.5 * step * q1, 0.5 * step * q4,
                         -0.5 * step * wx,  -0.5 * step * wy, -0.5 * step * wz,1,-0.5 * step * q1,-0.5 * step * q2,-0.5 * step * q3,
                        0,0,0,0,step * (I_inv[1][1] * (wz * I[2][1] - wy * I[3][1]) + I_inv[1][2] * (-wz * I[1][1] + 2 * I[3][1] * wx + I[3][2] * wy + I[3][3] * wz + hwz) + I_inv[1][3] * (wy * I[1][1] - 2 * I[2][1] * wx - I[2][2] * wy - I[2][3] * wz - hwy))+1,step * (I_inv[1][1] * (wz * I[2][2] - I[3][1] * wx - 2 * I[3][2] * wy - I[3][3] * wz - hwz) + I_inv[1][2] * (-wz * I[1][2] + wx * I[3][2]) + I_inv[1][3] * (I[1][1] * wx + 2 * I[1][2] * wy + I[1][3] * wz - wx * I[2][2] + hwx)),  step * (I_inv[1][1] * (I[2][1] * wx + I[2][2] * wy + 2 * I[2][3] * wz - wy * I[3][3] + hwy) + I_inv[1][2] * (-I[1][1] * wx - I[1][2] * wy - 2 * I[1][3] * wz + wx * I[3][3] - hwx) + I_inv[1][3] * (wy * I[1][3] - wx * I[2][3])),
                        0,0,0,0,step * (I_inv[2][1] * (wz * I[2][1] - wy * I[3][1]) + I_inv[2][2] * (-wz * I[1][1] + 2 * I[3][1] * wx + I[3][2] * wy + I[3][3] * wz + hwz) + I_inv[2][3] * (wy * I[1][1] - 2 * I[2][1] * wx - I[2][2] * wy - I[2][3] * wz - hwy)),  step * (I_inv[2][1] * (wz * I[2][2] - I[3][1] * wx - 2 * I[3][2] * wy - I[3][3] * wz - hwz) + I_inv[2][2] * (-wz * I[1][2] + wx * I[3][2]) + I_inv[2][3] * (I[1][1] * wx + 2 * I[1][2] * wy + I[1][3] * wz - wx * I[2][2] + hwx))+1,step * (I_inv[2][1] * (I[2][1] * wx + I[2][2] * wy + 2 * I[2][3] * wz - wy * I[3][3] + hwy) + I_inv[2][2] * (-I[1][1] * wx - I[1][2] * wy - 2 * I[1][3] * wz + wx * I[3][3] - hwx) + I_inv[2][3] * (wy * I[1][3] - wx * I[2][3])),
                        0,0,0,0,step * (I_inv[3][1] * (wz * I[2][1] - wy * I[3][1]) + I_inv[3][2] * (-wz * I[1][1] + 2 * I[3][1] * wx + I[3][2] * wy + I[3][3] * wz + hwz) + I_inv[3][3] * (wy * I[1][1] - 2 * I[2][1] * wx - I[2][2] * wy - I[2][3] * wz - hwy)),  step * (I_inv[3][1] * (wz * I[2][2] - I[3][1] * wx - 2 * I[3][2] * wy - I[3][3] * wz - hwz) + I_inv[3][2] * (-wz * I[1][2] + wx * I[3][2]) + I_inv[3][3] * (I[1][1] * wx + 2 * I[1][2] * wy + I[1][3] * wz - wx * I[2][2] + hwx)),  step * (I_inv[3][1] * (I[2][1] * wx + I[2][2] * wy + 2 * I[2][3] * wz - wy * I[3][3] + hwy) + I_inv[3][2] * (-I[1][1] * wx - I[1][2] * wy - 2 * I[1][3] * wz + wx * I[3][3] - hwx) + I_inv[3][3] * (wy * I[1][3] - wx * I[2][3])));
        float dt = step/10;
        for (int i = 0; i < 10; i++){
            wx = x_check[4];
            wy = x_check[5];
            wz = x_check[6];
            x_check = x_check + 0.5* vec7(mat4(0,wz,-wy,wx,
                                    -wz,0,wx,wy,
                                     wy,-wx,0,wz,
                                    -wx,-wy,-wz,0)*x_check(1:4)*dt,
            (I_inv*(cross(-vec3(x_check[4],x_check[5],x_check[6]),I*vec3(x_check[4],x_check[5],x_check[6])+Lw)-u))*dt); //predict state to t+dt
        }
        P_check = F*P_check*transpose(F)+Q; //update covariance matrix of state
        //**************************************Correction**********************************************************************

        if(eclipse){//eclipse case
            // Jacobian H eclipse
            HE = mat36(transpose(mat63(  2 * B_E[1] * q1 + 2 * B_E[2] * q2 + 2 * B_E[3] * q3,  2 * B_E[2] * q1 - 2 * B_E[1] * q2 - 2 * B_E[3] * q4, 2 * B_E[3] * q1 - 2 * B_E[1] * q3 + 2 * B_E[2] * q4, -2 * B_E[3] * q2 + 2 * B_E[2] * q3 + 2 * B_E[1] * q4, 0, 0, 0,
                                        -2 * B_E[2] * q1 + 2 * B_E[1] * q2 + 2 * B_E[3] * q4,  2 * B_E[1] * q1 + 2 * B_E[2] * q2 + 2 * B_E[3] * q3, 2 * B_E[3] * q2 - 2 * B_E[2] * q3 - 2 * B_E[1] * q4,  2 * B_E[3] * q1 - 2 * B_E[1] * q3 + 2 * B_E[2] * q4, 0, 0, 0,
                                        -2 * B_E[3] * q1 + 2 * B_E[1] * q3 - 2 * B_E[2] * q4, -2 * B_E[3] * q2 + 2 * B_E[2] * q3 + 2 * B_E[1] * q4, 2 * B_E[1] * q1 + 2 * B_E[2] * q2 + 2 * B_E[3] * q3, -2 * B_E[2] * q1 + 2 * B_E[1] * q2 + 2 * B_E[3] * q4, 0, 0, 0)));
            K = P_check*transpose(HE)*inverse((HE*P_check*transpose(HE)+R));
            x_check = x_check + K * ( vec3(B_B[0],B_B[1],B_B[2])-vec3(quat_rotation(B_E,vec4(-x_check[0],-x_check[1],-x_check[2],x_check[3]))));
            P_check = (mat7(1.0f)-K*HE)*P_check;

        }else{ //Not eclipse, normal conditions
            // Jacobian H
            H =  transpose(mat6( 2 * S_E[1] * q1 + 2 * S_E[2] * q2 + 2 * S_E[3] * q3,  2 * S_E[2] * q1 - 2 * S_E[1] * q2 - 2 * S_E[3] * q4, 2 * S_E[3] * q1 - 2 * S_E[1] * q3 + 2 * S_E[2] * q4, -2 * S_E[3] * q2 + 2 * S_E[2] * q3 + 2 * S_E[1] * q4, 0, 0, 0,
                                -2 * S_E[2] * q1 + 2 * S_E[1] * q2 + 2 * S_E[3] * q4,  2 * S_E[1] * q1 + 2 * S_E[2] * q2 + 2 * S_E[3] * q3, 2 * S_E[3] * q2 - 2 * S_E[2] * q3 - 2 * S_E[1] * q4,  2 * S_E[3] * q1 - 2 * S_E[1] * q3 + 2 * S_E[2] * q4, 0, 0, 0,
                                -2 * S_E[3] * q1 + 2 * S_E[1] * q3 - 2 * S_E[2] * q4, -2 * S_E[3] * q2 + 2 * S_E[2] * q3 + 2 * S_E[1] * q4, 2 * S_E[1] * q1 + 2 * S_E[2] * q2 + 2 * S_E[3] * q3, -2 * S_E[2] * q1 + 2 * S_E[1] * q2 + 2 * S_E[3] * q4, 0, 0, 0,
                                 2 * B_E[1] * q1 + 2 * B_E[2] * q2 + 2 * B_E[3] * q3,  2 * B_E[2] * q1 - 2 * B_E[1] * q2 - 2 * B_E[3] * q4, 2 * B_E[3] * q1 - 2 * B_E[1] * q3 + 2 * B_E[2] * q4, -2 * B_E[3] * q2 + 2 * B_E[2] * q3 + 2 * B_E[1] * q4, 0, 0, 0,
                                -2 * B_E[2] * q1 + 2 * B_E[1] * q2 + 2 * B_E[3] * q4,  2 * B_E[1] * q1 + 2 * B_E[2] * q2 + 2 * B_E[3] * q3, 2 * B_E[3] * q2 - 2 * B_E[2] * q3 - 2 * B_E[1] * q4,  2 * B_E[3] * q1 - 2 * B_E[1] * q3 + 2 * B_E[2] * q4, 0, 0, 0,
                                -2 * B_E[3] * q1 + 2 * B_E[1] * q3 - 2 * B_E[2] * q4, -2 * B_E[3] * q2 + 2 * B_E[2] * q3 + 2 * B_E[1] * q4, 2 * B_E[1] * q1 + 2 * B_E[2] * q2 + 2 * B_E[3] * q3, -2 * B_E[2] * q1 + 2 * B_E[1] * q2 + 2 * B_E[3] * q4, 0, 0, 0));
            K = P_check*transpose(H)*inverse((H*P_check*transpose(H)+R));
            x_check = x_check + K * ( vec6(S_B[0],S_B[1],S_B[2],B_B[0],B_B[1],B_B[2])-vec6(quat_rotation(S_E,vec4(-x_check[0],-x_check[1],-x_check[2],x_check[3])), quat_rotation(B_E,vec4(-x_check[0],-x_check[1],-x_check[2],x_check[3]))));
            P_check = (mat7(1.0f)-K*H)*P_check;
        }
        //**************************************Output value**********************************************************************

        vec4 q_BE = normalize(vec4(x_check[0],x_check[1],x_check[2],x_check[3]));
        x_check = vec7(q_BE,x_check[4],x_check[5],x_check[6]);
    }

}