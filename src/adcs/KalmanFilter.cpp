//
// Created by Charles on 4/9/2021.
//

void ekf_init(double &x_check[7], double &P_check[7][7], const double &R[6][6], dmat3 &RE, const double &Q[7][7], dmat3 &inv_I, dvec3 Se, dvec3 Be,double y[1][6]){



}

void triad(double &q_AB,dvec3 va1,dvec3 va2,dvec3 vb1,dvec3 vb2){
//normalize the vectors
    va1=glm::normalize(va1);
    va2=glm::normalize(va2);
    vb1=glm::normalize(vb1);
    vb2=glm::normalize(vb2);
//cross product to get the normal vector
    dvec3 cross_a = glm::normalize(glm::cross(va1,va2));
    dvec3 cross_b = glm::normalize(glm::cross(vb1,vb2));
//Triad in DCM
    dmat3 DCM_AB =
}