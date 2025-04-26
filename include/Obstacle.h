#ifndef OBSTACLE_H
#define OBSTACLE_H

#pragma once

#include "Vertex.h"
#include "Animation.h"
#include <armadillo>
#include "Obj.h"
#include "Ply.h"

class Obstacle
{
public:
    Obstacle(Vertex initial_pos);
    
    void draw();

private:
    Vertex initial_pos;

    Obj person;
    Ply cactus;
    
    arma::Mat<float> transform;

    Vertex E1, E2;

};

#endif