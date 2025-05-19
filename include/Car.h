#ifndef CAR_H
#define CAR_H

#pragma once

#include "Vertex.h"
#include "Animation.h"
#include <armadillo>
#include "Obj.h"
#include "Ply.h"
#include "Triangle.h"

/**
 * * @brief Esta clase es usada para crear y dibujar un objeto Car. Clase Car:: Car object
 */
class Car
{
public:
    Car(Vertex initial_pos, GLuint programID);
    
    void draw();
    void set_view(unsigned int key);
    void set_projection(unsigned int key);

private:
    Vertex initial_pos;

    Obj car;
    Triangle car_data;

    glm::mat4 transform;

    Vertex E1, E2;

    GLuint programID;
    glm::mat4 view;
    glm::mat4 projection;
};

#endif