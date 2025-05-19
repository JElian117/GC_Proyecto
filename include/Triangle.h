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
#include <glm/gtc/matrix_transform.hpp>


using namespace std;

/**
 * * @brief Esta clase es usada para crear un objeto Triangle, para procesar el buffer de datos y colores. Clase Triangle:: Triangle object
 */
class Triangle
{
public:
    Triangle();
    Triangle(vector <GLfloat> vertex_buffer_data, vector <GLfloat> color_buffer_data);
    void set_data(vector <GLfloat> vertex_buffer_data, vector <GLfloat> color_buffer_data);
    void draw(GLuint programID, glm::mat4 mvp);

private:
    GLuint vertexbuffer;
	GLuint colorbuffer;
    GLuint datasize;
};

#endif