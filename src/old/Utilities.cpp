//
// Created by Charles on 4/9/2021.
//

#include "old/Utilities.h"
namespace adcs {

    void triad(mat3 &dcm_AB, vec3 va1, vec3 va2, vec3 vb1, vec3 vb2) {
//normalize the vectors
        va1 = normalize(va1);
        va2 = normalize(va2);
        vb1 = normalize(vb1);
        vb2 = normalize(vb2);
//cross product to get the normal vector
        vec3 cross_a = normalize(cross(va1, va2));
        vec3 cross_b = normalize(cross(vb1, vb2));
//Triad in DCM
        dcm_AB = transpose(mat3(va1, normalize(cross(cross_a, va1)), cross_a) *
                           mat3(vb1, normalize(cross(cross_b, vb1)), cross_b));
    }

    vec4 DCM2Quat(mat3 dcm_AB) {

        float tr = dcm_AB[1][1] + dcm_AB[2][2] + dcm_AB[3][3];
        float S;
        float qw;
        float qx;
        float qy;
        float qz;

        if (tr > 0) {
            S = sqrt(tr + 1.0) * 2.0; // S=4*qw
            qw = 0.25 * S;
            qx = (dcm_AB[3][2] - dcm_AB[2][3]) / S;
            qy = (dcm_AB[1][3] - dcm_AB[3][1]) / S;
            qz = (dcm_AB[2][1] - dcm_AB[1][2]) / S;
        } else if ((dcm_AB[1][1] > dcm_AB[2][2]) && (dcm_AB[1][1] > dcm_AB[3][3])) {
            S = sqrt(1.0 + dcm_AB[1][1] - dcm_AB[2][2] - dcm_AB[3][3]) * 2.0; // S=4*qx
            qw = (dcm_AB[3][2] - dcm_AB[2][3]) / S;
            qx = 0.25 * S;
            qy = (dcm_AB[1][2] + dcm_AB[2][1]) / S;
            qz = (dcm_AB[1][3] + dcm_AB[3][1]) / S;
        } else if (dcm_AB[2][2] > dcm_AB[3][3]) {
            S = sqrt(1.0 + dcm_AB[2][2] - dcm_AB[1][1] - dcm_AB[3][3]) * 2.0; // S=4*qy
            qw = (dcm_AB[1][3] - dcm_AB[3][1]) / S;
            qx = (dcm_AB[1][2] + dcm_AB[2][1]) / S;
            qy = 0.25 * S;
            qz = (dcm_AB[2][3] + dcm_AB[3][2]) / S;
        } else {
            S = sqrt(1.0 + dcm_AB[3][3] - dcm_AB[1][1] - dcm_AB[2][2]) * 2.0; // S=4*qz
            qw = (dcm_AB[2][1] - dcm_AB[1][2]) / S;
            qx = (dcm_AB[1][3] + dcm_AB[3][1]) / S;
            qy = (dcm_AB[2][3] + dcm_AB[3][2]) / S;
            qz = 0.25 * S;
        }
        vec4 q_AB = {qx, qy, qz, qw};
        return q_AB;
    }

    vec4 quat_multiply(vec4 qa, vec4 qb) {
        double q4 = qa[4] * qb[4] - qa[1] * qb[1] - qa[2] * qb[2] - qa[3] * qb[3];
        double q1 = qa[4] * qb[1] + qa[1] * qb[4] + qa[2] * qb[3] - qa[3] * qb[2];
        double q2 = qa[4] * qb[2] - qa[1] * qb[3] + qa[2] * qb[4] + qa[3] * qb[1];
        double q3 = qa[4] * qb[3] + qa[1] * qb[2] - qa[2] * qb[1] + qa[3] * qb[4];

        return vec4(q1, q2, q3, q4);
    }

    vec3 quat_rotation(vec3 be, vec4 cq_be) {
        vec4 be4 = vec4(be.x, be.y, be.z, 0);

        vec4 q = quat_multiply(cq_be, be4);

        vec4 qb = vec4(-1) * cq_be;

        vec4 finalq = quat_multiply(q, qb);
        return vec3(finalq.x, finalq.y, finalq.z);
    }
}