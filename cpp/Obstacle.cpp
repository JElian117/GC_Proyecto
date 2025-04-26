// Created by JElian117 on 10/11/2023.

#include "../include/Obstacle.h"

Obstacle::Obstacle (Vertex inital_pos){
    Animation an;

    this->initial_pos = inital_pos;

    //this->transform = an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z())
    //Paso 1: Escalar. Paso 2: Rotar respecto de 'Y'. Paso 3: Trastadar respecto a 'X' un poco a la izquierda.
    //this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z()) *
    //                    an.Ry(90) * an.S(0.05, 0.05, 0.05);
    //Escalar y llevar a posición inicial                    
    this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z()) *
                        an.S(0.05, 0.05, 0.05);

    this->person.set_file_name("Models/person.obj");
    this->person.set_transform(this->transform);
    this->person.set_color(0.0, 0.0, 1.0);

    this->cactus.set_file_name("Models/cactus.ply");
    this->cactus.set_transform(this->transform);
    this->cactus.set_color(1.0, 0.0, 0.0);
}

void Obstacle::draw(){
    Animation an;

    this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z()) *
                        an.S(0.05, 0.05, 0.05);

    this->person.draw();
    this->cactus.draw();
}