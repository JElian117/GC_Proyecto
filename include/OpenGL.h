#ifndef OPENGL_H
#define OPENGL_H

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

/**
 * * @brief Esta clase es usada para crear la ventana y cargar los shaders. Clase OpenGL:: OpenGL object
 */
class OpenGL
{
public:
    OpenGL();
    GLFWwindow* createWindow(long width, long height, std::string title);
    GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);
    GLuint getProgramID();
private:
    GLuint programID;

};

#endif