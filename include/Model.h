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

class Model{
public:
    Model(string file_name);
    Model();
    void print();
    void set_transform(arma::Mat<float> transform);
    void set_color(float r, float g, float b);
    void draw();
protected:
    vector<Vertex> vertices;
    vector<Face> faces;
    vector<string> split(const string& str, const char& delim);
    virtual void load(string file_name) = 0;
    arma::Mat<float> transform;
    float r, g, b;
};
#endif