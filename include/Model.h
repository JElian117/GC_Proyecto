#ifndef MODEL_H
#define MODEL_H

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Vertex.h"
#include "Face.h"
#include "Triangle.h"

using namespace std;

/**
 * * @brief Esta clase es usada para crear modelos usando Obj y Ply. Clase Model:: Model object
 */
class Model{
public:
    Model(string file_name);
    Model();
    void print();
    void set_transform(glm::mat4 transform);
    glm::mat4 get_transform();
    void set_color(float r, float g, float b);
    vector<GLfloat> get_vertex_buffer_data();
    vector<GLfloat> get_vertex_color_data();

protected:
    vector<Vertex> vertices;
    vector<Face> faces;
    vector<string> split(const string& str, const char& delim);
    virtual void load(string file_name) = 0;
    glm::mat4 model;
    float r, g, b;
};
#endif