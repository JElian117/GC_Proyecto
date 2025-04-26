#ifndef CAR_H
#define CAR_H

#pragma once

#include "Vertex.h"
#include "Animation.h"
#include <armadillo>
#include "Obj.h"
#include "Ply.h"

class Car
{
public:
    Car(Vertex initial_pos);
    
    void draw();

private:
    Vertex initial_pos;

    Obj car;

    arma::Mat<float> transform;

    Vertex E1, E2;

};

#endif