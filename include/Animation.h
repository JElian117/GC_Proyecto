#ifndef ANIMATION_H
#define ANIMATION_H

#pragma once

#include "Vertex.h"
#include <math.h>
#include <vector>
#include <armadillo>

using namespace std;

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
    arma::Mat<float>Rp1p2(float theta, Vertex P1, Vertex P2);

};

#endif