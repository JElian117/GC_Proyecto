#ifndef CAR_H
#define CAR_H

#pragma once

#include "Vertex.h"
#include "Animation.h"
#include <armadillo>
#include "Obj.h"
#include "Ply.h"
#include "Triangle.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

/**
 * * @brief Esta clase es usada para crear y dibujar un objeto Car, para manejar el view (POV) de la escena, manejar la proyección y proporcionar los métodos necesarios para simular el movimiento del carro que son setters para la velocidad y dirección en cuestión de manejo del volante, un método para actualizar la posición del carro y un getter de la velocidad del carro. Clase Car:: Car object
 */
class Car
{
public:
    Car(Vertex initial_pos, GLuint programID);
    
    void draw();
    void set_view(unsigned int key);
    void set_projection(unsigned int key);

    // Métodos para simular el movimiento del carro
    void set_speed(float inc);
    void set_steering(float inc);
    void update_position();
    float get_speed();
    void reset();

private:
    Vertex initial_pos;
    Vertex current_pos;
    float speed;
    float steering_angle; // Ángulo de dirección

    Obj car;
    Triangle car_data;

    glm::mat4 transform;

    Vertex E1, E2;

    GLuint programID;
    glm::mat4 view;
    glm::mat4 projection;

    // Para la animación de movimiento
    vector<Vertex> trajectory;
    bool is_moving;
    unsigned int move_index;
    
    // Ejes para rotación
    Vertex rotation_axis_p1;
    Vertex rotation_axis_p2;
};

#endif