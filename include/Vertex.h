#ifndef VERTEX_H
#define VERTEX_H

#pragma once

#include <iostream>
#include <string>
#include <armadillo>

using namespace std;

class Vertex //Definición de la clase
{
private:
    float x, y, z;
public:
    Vertex();
    Vertex(float x, float y, float z);
    void print();

    Vertex operator-(Vertex op2);
    Vertex operator*(float op2);
    Vertex operator+(Vertex op2);
    //Hay un destructor de la clase ~Vertex(); pero al menos por el momento no lo necesitamos y por lo tanto no lo vamos a implementar

    float get_x();
    float get_y();
    float get_z();
    void set_x(float x);
    void set_y(float y);
    void set_z(float z);

    void octant();
    arma::Col<float> h();
};

#endif