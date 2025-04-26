#include <iostream>
#include "include/Vertex.h"
#include "include/Car.h"
#include "include/Obstacle.h"
#include "include/OpenGL.h"
#include "include/Triangle.h"

using namespace std;

int main(){
    Vertex initial_pos(-0.8, 0, 0);
    Car car(initial_pos);
    cout<<"Carro cargado con éxito"<<endl;
    
    Obstacle obstacle(initial_pos);
    cout<<"Obstaculo(s) cargado(s) con éxito"<<endl;

    OpenGL gl = OpenGL();

    GLFWwindow *window = gl.createWindow(1000, 600, "Carro y Obstaculo");
    if( window == NULL )
        return -1;

    do {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        car.draw();
        obstacle.draw();

        glfwSwapBuffers(window);
        
    } while ( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

    return 0;
}