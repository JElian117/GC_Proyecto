#ifndef OBSTACLE_H
#define OBSTACLE_H

#pragma once

#include "Vertex.h"
#include "Animation.h"
#include <armadillo>
#include "Obj.h"
#include "Ply.h"
#include "Triangle.h"

/**
 * * @brief Esta clase es usada para crear y dibujar un objeto Obstacle. Clase Obstacle:: Obstacle object
 */
class Obstacle
{
public:
    Obstacle(Vertex initial_pos, GLuint programID);

    void set_view(unsigned int key);
    void set_projection(unsigned int key);
    
    void draw();

private:
    Vertex initial_pos;

    Obj person;
    Triangle person_data;
    Ply cactus;
    Triangle cactus_data;
    
    glm::mat4 transform;

    Vertex E1, E2;

    GLuint programID;
    glm::mat4 view;
    glm::mat4 projection;

};

#endif