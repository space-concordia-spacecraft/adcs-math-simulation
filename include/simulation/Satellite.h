#pragma once
#include "adcs/Utils.h"
#include "adcs/Modes.h"

/*
 * P/R -> Position Vector
 * V -> Velocity Vector
 * S -> Sun Vector
 *
 */

namespace adcs::satellite {
    class Satellite {

    public:
        Satellite();

        void updateMode();
        void updateMode(int mode);

        // Setters
        void setMomentOfInertia(vec3 momentOfInertia);
        void setProductOfInertia(vec3 productOfInertia);

        // Getters
        vec3 getMomentOfInertia();
        vec3 getProductOfInertia();

    private:

        // Mode Properties
        int m_Mode;
        bool m_ManualModeSelection = false;

        // Inertia Properties
        vec3 m_MomentOfInertia = vec3(0.04582275, 0.04561065, 0.0085932349);
        vec3 m_ProductOfInertia = vec3(0.000947555, -0.000072545546, -0.000031658756);

        // Fixed-Body Coordinate System
        vec3 m_Rvector, m_Vvector, m_Avector, m_Bvector, m_Svector;

    };
}