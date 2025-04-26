#ifndef CANNON_H
#define CANNON_H

#pragma once

#include "Vertex.h"
#include "Animation.h"
#include <armadillo>
#include "Obj.h"
#include "Ply.h"

class Cannon{
public:
    Cannon(Vertex initial_pos);

    void set_angle(float inc);
    void set_force(float force);

    void shoot();
    void draw();
    void reset();

private:
    Vertex initial_pos;
    float angle;
    float force;

    Obj body;
    Obj bullet;
    Ply l_wheel;
    Ply r_wheel;
    
    arma::Mat<float> transform;
    vector<Vertex> trajectory;

    Vertex E1, E2; //Ejes para rotar el cuerpo del cañón

    bool shooted;
    unsigned int i_shoot;
};
#endif