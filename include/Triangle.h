#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

using namespace std;

class Triangle
{
public:
    Triangle(vector <GLfloat> vertex_buffer_data, vector <GLfloat> color_buffer_data);
    void draw();

private:
    GLuint vertexbuffer;
	GLuint colorbuffer;
    GLuint datasize;
};

#endif