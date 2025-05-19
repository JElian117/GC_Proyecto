#include <iostream>
#include "include/Vertex.h"
#include "include/Car.h"
#include "include/Obstacle.h"
#include "include/OpenGL.h"

using namespace std;

int main(){
    OpenGL gl = OpenGL();
    
    GLFWwindow *window = gl.createWindow(1000, 600, "Carro y Obstaculo");
    if( window == NULL )
    return -1;
    
    Vertex initial_pos(-0.8, 0, 0);
    Obstacle obstacle(initial_pos, gl.getProgramID());
    Car car(initial_pos, gl.getProgramID());
    
    cout<<"Carro cargado con éxito"<<endl;
    cout<<"Obstaculo(s) cargado(s) con éxito"<<endl;

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    do {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        car.draw();
        obstacle.draw();

        glfwSwapBuffers(window);
		glfwPollEvents();

        // Cambiar la vista del carro y el obstáculo.
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
            car.set_view(1);
            obstacle.set_view(1);
        }
        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
            car.set_view(2);
            obstacle.set_view(2);
        }
        else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
            car.set_view(3);
            obstacle.set_view(3);
        }
        else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS){
            car.set_view(4);
            obstacle.set_view(4);
        }
        
    } while ( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

    return 0;
}