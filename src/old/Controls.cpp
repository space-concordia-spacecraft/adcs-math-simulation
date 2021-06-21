#include <cmath>

#include "old/Modes.h"
#include "old/Controls.h"
#include "old/Utilities.h"

namespace adcs::controls {

    int currentMode = 0;

    bool eclipse_prediction(vec3 se, vec3 pe) {
        if(glm::dot(se, pe)/(glm::length(se)*glm::length(pe)) <= -0.32556815){
            return 1;
        } else {
            return 0;
        }
    }

    vec4 quat_multiply(vec4 qa, vec4 qb) {
        double q4 = qa[4]*qb[4] - qa[1]*qb[1] - qa[2]*qb[2] - qa[3]*qb[3];
        double q1 = qa[4]*qb[1] + qa[1]*qb[4] + qa[2]*qb[3] - qa[3]*qb[2];
        double q2 = qa[4]*qb[2] - qa[1]*qb[3] + qa[2]*qb[4] + qa[3]*qb[1];
        double q3 = qa[4]*qb[3] + qa[1]*qb[2] - qa[2]*qb[1] + qa[3]*qb[4];

        return vec4(q1, q2, q3, q4);
    }

    vec3 saturation(vec3 b) {
        vec3 temp = vec3(b);

        temp.x *= abs(temp.x)/CONST_MAGNETORQUER_SATURATION_X;
        temp.y *= abs(temp.y)/CONST_MAGNETORQUER_SATURATION_Y;
        temp.z *= abs(temp.z)/CONST_MAGNETORQUER_SATURATION_Z;

        // max
        double max = 1;

        for(int i = 0; i < 3; i ++) {
            if(temp[i] > max)
                max = temp[i];
        }

        b /= max;

        return b;
    }

    // 1- Click on block
    // 2- How many inputs and outputs
    vec3 bdot_controller(vec3 b) {
        vec3 m = vec3(0,0,0);
        b += m; // b = b+m
        b *= 0.5;

        b *= -3e7;

        return saturation(b);
    }

    vec3 targetFrameVelocity(vec4 quaternion_earth_target) {
        quaternion_earth_target[3] *= -1.0f;
        vec4 integrated_quaternion = filtered_derivative(quaternion_earth_target);

        vec4 result = quat_multiply(integrated_quaternion, quaternion_earth_target);
        result *= 2.0f;

        return vec3(result[0], result[1], result[2]);
    }

    void momentum_control(int mode, int eclipse, int &C_M, vec3 &m) {

    }

    int modeSelection(int modeOverdrive, vec3 namibia, vec3 ground, vec3 argentina, vec3 p, bool eclipse, vec3 lTot){
        if(modeOverdrive == 0) {
            if(currentMode == 6 && glm::length(lTot) > 0.9e-3)
                currentMode = MODE_DETUMBLING;
            else if(max(abs(glm::length(lTot)))>1.7e-3)
                currentMode = MODE_DETUMBLING;
            else if(eclipse == 1)
                currentMode = MODE_NADIR;
            else if(glm::dot(p, argentina)/(glm::length(p) * glm::length(argentina)) > 0.96)
                currentMode = MODE_ARGENTINA;
            else if(glm::dot(p, namibia)/(glm::length(p) * glm::length(namibia)) > 0.96)
                currentMode = MODE_NAMIBIA;
            else if(glm::dot(p, ground)/(glm::length(p) * glm::length(ground)) > 0.91)
                currentMode = MODE_GROUND;
            else
                currentMode = MODE_SUN;
        } else {
            currentMode = modeOverdrive;
        }

    }

    vec4 momentum_bias(vec3 ve, vec3 pe, quat cbe) {

        vi= glm::cross(ve,pe);

        //Rotation
        vec4 vi4=vec4(vi,0);
        qa = glm::dot(cbe, vi4);
        vector<int> v{-1, -1, -1, 1};
        qb = glm::dot(cbe, v);
        vo = glm::dot(qa, qb);

        u=glm::normalize(vo);
        u*= -0.5e-3;

        return vec4(result[0], result[1], result[2]);
    }



    vec3 rotation(vec3 be, vec4 cq_be) {
        vec4 be4 = vec4(be.x, be.y, be.z, 0);

        vec4 q = quat_multiply(cq_be, be4);

        vec4 qb = vec4(-1) * cq_be;

        vec4 finalq = quat_multiply(q, qb);
        return vec3(finalq.x, finalq.y, finalq.z);
    }

    void body_earth_estimation() {

    }

    void torque_saturation(const double tw[3], double out[3]) {

        // TODO: Figure out what wheel_saturation is
        const double wheel_saturation = 1;


    }

    void saturation_rw(const double lw[3], const double ti[3], double out[3]) {
        double sat1 = abs(lw[0]) / 1.6e-3;
        double sat2 = abs(lw[1]) / 1.6e-3;
        double sat3 = abs(lw[2]) / 1.6e-3;

        out[0] = (sat1 > 1 && ti[0] * lw[0] > 0) ? 0 : ti[0];
        out[1] = (sat2 > 1 && ti[1] * lw[1] > 0) ? 0 : ti[1];
        out[2] = (sat3 > 1 && ti[2] * lw[2] > 0) ? 0 : ti[2];
    }

    void selector(int mode, const double lwheel[3], const double nominal[3], const double calibration[3],
                  double out[3]) {
        switch (mode) {
            case MODE_DETUMBLING:
                out[0] = -0.5 * lwheel[0];
                out[1] = -0.5 * lwheel[1];
                out[2] = -0.5 * lwheel[2];
                return;
            case MODE_OFF:
                out[0] = 0;
                out[1] = 0;
                out[2] = 0;
                return;
            case MODE_CALIBRATION:
                out[0] = calibration[0];
                out[1] = calibration[1];
                out[2] = calibration[2];
                return;
            default:
                out[0] = nominal[0];
                out[1] = nominal[1];
                out[2] = nominal[2];
                return;
        }
    }


}

