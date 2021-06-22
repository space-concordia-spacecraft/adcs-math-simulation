#pragma once
#include "Utils.h"
#include "Modes.h"

namespace adcs::satellite {
    class Satellite {

    public:
        Satellite();

        // Setters
        void setMomentOfInertia(vec3 momentOfInertia);
        void setProductOfInertia(vec3 productOfInertia);

        void setMode(int mode);

        // Getters
        vec3 getMomentOfInertia();
        vec3 getProductOfInertia();

    private:

        // Mode Properties
        int m_Mode;
        bool m_ManualModeSelection = false;

        // Sun Position
        vec3 m_SunVector;

        // Inertia Properties
        vec3 m_MomentOfInertia = vec3(0.04582275, 0.04561065, 0.0085932349);
        vec3 m_ProductOfInertia = vec3(0.000947555, -0.000072545546, -0.000031658756);

        // TEME Coordinate System
        vec3 m_Rteme, m_Steme, m_Vteme, m_Ateme;

        // ITRF Coordinate System
        vec3 m_Recef, m_Secef, m_Vecef, m_Aecef;

        // Fixed-Body Coordinate System
        vec3 m_Rvector, m_Vvector, m_Avector, m_Bvector;

    };
}