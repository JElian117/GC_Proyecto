#include "../include/Face.h"

using namespace std;

/**
 * @brief Constructor de la clase Face:: Face object
 * @param vector<unsigned int> vertices Vértices del objeto
 */
Face::Face(vector<unsigned int> vertices)
{
    this->vertices = vertices;
}
//Template, definimos el tipo de datos de los elementos vector<template> objeto

/**
 * @brief Método que imprime los vértices del objeto
 */
void Face::print()
{
    // cout << "Face:" <<endl;
    // for (Vertex v : this->vertices)
    // {
    //     v.print();
    // }
}

/**
 * @brief Método que regresa los vértices del objeto
 * @return vector<unsigned int> Vértices del objeto
 */
vector<unsigned int> Face::get_vertices() const {
    return vertices;
}