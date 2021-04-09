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




}