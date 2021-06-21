#include "Controls.h"
#include <cmath>
#include "adcs/MathTimeLib.h"

//mathtimeslib has cross, but not sure if vec3 are arrays
namespace adcs::controls {
    vec3 SE,PE,VE,NE,AE,GE,pointingE,constraintE,pointingB,constraintB;
    void Guidance(int mode,vec3 se,vec3 pe,vec3 ve,vec3 ne,vec3 ae,vec3 ge,vec3 pointingE,vec3 constraintE,vec3 pointingB,vec3 constraintB,vec4 &q_BTarget, vec4 &q_ETarget){

        switch(mode){

            case 1:
                // sun
                pointingE = SE;
                constraintE = VE;
                if (dot(SE,cross(VE,PE))>0) pointingB = { 1, -1, 0 };
                else  pointingB = { 1, -1, 0 };

                pointingB = { 0, 0, 1 };
                //what does end do
                constraintB = { 0, 0, 1 };
            break;
            case 2: //ground
                pointingE = PE;
                constraintE = VE;
                pointingB = {0,0,1};
                constraintB = {0,1,0};
            break;
            case 3: //Imaging Argentina
                pointingE = AE-PE;
                constraintE = VE;
                pointingB = {0,1,0};
                constraintB = {0,0,1};
            break;
            case 4: //Imaging Namibia
                pointingE = VE;
                constraintE = NE-PE;
                pointingB = {0,0,1};
                constraintB = {0,1,0};
            break;
            default: //Nadir
                pointingE = VE;
                constraintE = PE;
                pointingB = {0,0,1};
                constraintB = {0,-1,0};
        }

    //Guidance block done. Next is TRIAD
    vec3 input1,input2,input3, input4, input5, input6;
    input1 = glm::normalize(pointingE);//first input of the first concatenate
    input3 = glm::normalize(glm::cross(pointingE,constraintE));
    input2 = glm::normalize(glm::cross(input1,input3));

        input4 = glm::normalize(pointingB);
        input6 = glm::normalize(glm::cross(pointingB,constraintB));
        input5 = glm::normalize(glm::cross(input6,input4));

        mat3 dcm = glm::matrixCompMult(mat3(input1,input2,input3),glm::transpose(mat3(input4,input5,input6)));
//-------------------------------function fcn
        double tr = dcm[1][1] + dcm[2][2] + dcm[3][3]; // calculates the trace
        double qx,qy,qz,qw,S;

        if (tr > 0) {
            S = sqrt(tr + 1.0) * 2; // S=4*qw
            qw = 0.25 * S;
            qx = (dcm[3][2] - dcm[2][3]) / S;
            qy = (dcm[1][3] - dcm[3][1]) / S;
            qz = (dcm[2][1] - dcm[1][2]) / S;
        }
            else if((dcm[1][1] > dcm[2][2]) && (dcm[1][1] > dcm[3][3])){
            S = sqrt(1.0 + dcm[1][1] - dcm[2][2] - dcm[3][3]) * 2; // S=4*qx
            qw = (dcm[3][2] - dcm[2][3]) / S;
            qx = 0.25 * S;
            qy = (dcm[1][2] + dcm[2][1]) / S;
            qz = (dcm[1][3] + dcm[3][1]) / S;
        }

        else if (dcm[2][2] > dcm[3][3]) {
            S = sqrt(1.0 + dcm[2][2] - dcm[1][1] - dcm[3][3]) * 2; // S=4*qy
            qw = (dcm[1][3] - dcm[3][1]) / S;
            qx = (dcm[1][2] + dcm[2][1]) / S;
            qy = 0.25 * S;
            qz = (dcm[2][3] + dcm[3][2]) / S;
        }
        else {
            S = sqrt(1.0 + dcm[3][3] - dcm[1][1] - dcm[2][2]) * 2; // S=4*qz
            qw = (dcm[2][1] - dcm[1][2]) / S;
            qx = (dcm[1][3] + dcm[3][1]) / S;
            qy = (dcm[2][3] + dcm[3][2]) / S;
            qz = 0.25 * S;
        }
        q_ETarget = vec4 (qx,qy,qz,qw);
        //how does the function output this
    }

}