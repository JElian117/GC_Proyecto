#include "../include/Face.h"

using namespace std;

Face::Face(vector<unsigned int> vertices)
{
    this->vertices = vertices;
}
//Template, definimos el tipo de datos de los elementos vector<template> objeto

void Face::print()
{
    // cout << "Face:" <<endl;
    // for (Vertex v : this->vertices)
    // {
    //     v.print();
    // }
}

vector<unsigned int> Face::get_vertices() const {
    return vertices;
}