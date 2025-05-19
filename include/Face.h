#ifndef FACE_H
#define FACE_H

#pragma once

#include "Vertex.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * * @brief Esta clase es usada para crear un objeto Face. Clase Face:: Face object
 */
class Face
{
private:
    vector<unsigned int> vertices;
public:
    Face(vector<unsigned int> vertices);
    void print();
    vector<unsigned int> get_vertices() const;
};

#endif