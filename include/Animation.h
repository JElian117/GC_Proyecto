#ifndef ANIMATION_H
#define ANIMATION_H

#pragma once

#include "Vertex.h"
#include <math.h>
#include <vector>
#include <armadillo>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

/**
 * * @brief Esta clase es usada para crear animaciones usando las curvas de Hermite y Bézier. Clase Animation:: Animation object
 */
class Animation{
public:
    Animation();

    vector<Vertex> move_line(Vertex P1, Vertex P2, float dt);
    vector<Vertex> move_hermite(Vertex P1, Vertex P4, Vertex R1, Vertex R4, float dt);
    vector<Vertex> move_bezier(Vertex P1, Vertex P2, Vertex P3, Vertex P4, float dt);
    
    arma::Mat<float> T(float dx,float dy, float dz);
    arma::Mat<float> S(float sx,float sy, float sz);
    arma::Mat<float> Rx(float theta);
    arma::Mat<float> Ry(float theta);
    arma::Mat<float> Rz(float theta);
    arma::Mat<float> Rp1p2(float theta, Vertex P1, Vertex P2);

    glm::mat4 T(float dx,float dy, float dz, bool t);
    glm::mat4 S(float sx,float sy, float sz, bool t);
    glm::mat4 Rx(float theta, bool t);
    glm::mat4 Ry(float theta, bool t);
    glm::mat4 Rz(float theta, bool t);
    glm::mat4 Rp1p2(float theta, Vertex P1, Vertex P2, bool t);
};

#endif