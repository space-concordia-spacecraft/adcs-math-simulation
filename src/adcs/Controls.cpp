//
// Created by Ruben on 3/27/2021.
//

#include "adcs/Controls.h"
#include <cmath>

namespace adcs::controls {

    bool eclipse_prediction(dvec3 se, dvec3 pe) {
        if(glm::dot(se, pe)/(glm::length(se)*glm::length(pe)) <= -0.32556815){
            return 1;
        } else {
            return 0;
        }
    }

    int modeSelection(){

    }
}