#include <cmath>

#include "adcs/Modes.h"
#include "adcs/Controls.h"

namespace adcs {
    namespace controls {


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

    bool eclipse_prediction(dvec3 se, dvec3 pe) {
        if(glm::dot(se, pe)/(glm::length(se)*glm::length(pe)) <= -0.32556815){
            return 1;
        } else {
            return 0;
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

    int modeSelection(){

    }

}