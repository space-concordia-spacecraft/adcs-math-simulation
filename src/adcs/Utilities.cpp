//
// Created by Charles on 4/9/2021.
//

#include "adcs/Utilities.h"
namespace adcs {

    void triad(mat3 &dcm_AB,vec3 va1,vec3 va2,vec3 vb1,vec3 vb2){
//normalize the vectors
        va1=normalize(va1);
        va2=normalize(va2);
        vb1=normalize(vb1);
        vb2=normalize(vb2);
//cross product to get the normal vector
        vec3 cross_a = normalize(cross(va1,va2));
        vec3 cross_b = normalize(cross(vb1,vb2));
//Triad in DCM
        dcm_AB = transpose(mat3(va1, normalize(cross(cross_a,va1)), cross_a)*
                mat3(vb1, normalize(cross(cross_b,vb1)), cross_b));
    }
    vec4 DCM2Quat(mat3 dcm_AB){

     float  tr = dcm_AB[1][1]+dcm_AB[2][2]+dcm_AB[3][3];
     float S;
     float qw;
     float qx;
     float qy;
     float qz;

    if (tr>0){
         S = sqrt(tr+1.0) * 2.0; // S=4*qw
         qw = 0.25 * S;
         qx = (dcm_AB[3][2] - dcm_AB[2][3]) / S;
         qy = (dcm_AB[1][3] - dcm_AB[3][1]) / S;
         qz = (dcm_AB[2][1] - dcm_AB[1][2]) / S;
    }else if ((dcm_AB[1][1] > dcm_AB[2][2]) && (dcm_AB[1][1] > dcm_AB[3][3])){
         S = sqrt(1.0 + dcm_AB[1][1] - dcm_AB[2][2] - dcm_AB[3][3]) * 2.0; // S=4*qx
         qw = (dcm_AB[3][2] - dcm_AB[2][3]) / S;
         qx = 0.25 * S;
         qy = (dcm_AB[1][2] + dcm_AB[2][1]) / S;
         qz = (dcm_AB[1][3] + dcm_AB[3][1]) / S;
    }else if (dcm_AB[2][2] > dcm_AB[3][3]){
         S = sqrt(1.0 + dcm_AB[2][2] - dcm_AB[1][1] - dcm_AB[3][3]) * 2.0; // S=4*qy
         qw = (dcm_AB[1][3] - dcm_AB[3][1]) / S;
         qx = (dcm_AB[1][2] + dcm_AB[2][1]) / S;
         qy = 0.25 * S;
         qz = (dcm_AB[2][3] + dcm_AB[3][2]) / S;
    }else {
         S = sqrt(1.0 + dcm_AB[3][3] - dcm_AB[1][1] - dcm_AB[2][2]) * 2.0; // S=4*qz
         qw = (dcm_AB[2][1] - dcm_AB[1][2]) / S;
         qx = (dcm_AB[1][3] + dcm_AB[3][1]) / S;
         qy = (dcm_AB[2][3] + dcm_AB[3][2]) / S;
         qz = 0.25 * S;
    }
    vec4 q_AB={qx,qy,qz,qw};
    return q_AB;
    }
}