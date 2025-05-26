#include <iostream>
#include "include/Vertex.h"
#include "include/Car.h"
#include "include/Obstacle.h"
#include "include/OpenGL.h"

using namespace std;

int main(){
    OpenGL gl = OpenGL();
    
    GLFWwindow *window = gl.createWindow(800, 600, "Carro y Obstaculo");
    if( window == NULL )
    return -1;
    
    Vertex initial_pos(-0.8, 0, 0);
    Obstacle obstacle(initial_pos, gl.getProgramID());
    Car car(initial_pos, gl.getProgramID());
    
    cout<<"Carro cargado con éxito"<<endl;
    cout<<"Obstaculo(s) cargado(s) con éxito"<<endl;

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Variables para control de teclas
    bool release_up = true, release_down = true;
    bool release_left = true, release_right = true;
    bool release_space = true, release_r = true;

    do {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        car.draw();
        obstacle.draw();

        glfwSwapBuffers(window);
		glfwPollEvents();

        //Controles del carro
        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && release_up) {
            release_up = false;
            car.set_speed(0.1f);
            car.update_position();
        }
        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {
            release_up = true;
        }

        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && release_down) {
            release_down = false;
            car.set_speed(-0.025f);
            car.update_position();
        }
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
            release_down = true;
        }

        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && release_left) {
            release_left = false;
            car.set_steering(5.0f);
            if(car.get_speed() > 0) car.update_position();
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE) {
            release_left = true;
        }

        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && release_right) {
            release_right = false;
            car.set_steering(-5.0f);
            if(car.get_speed() > 0) car.update_position();
        }
        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
            release_right = true;
        }

        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && release_space) {
            release_space = false;
            car.set_speed(-1.0f); //Frenar
        }
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
            release_space = true;
        }

        if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && release_r) {
            release_r = false;
            car.reset();
        }
        if(glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
            release_r = true;
        }

        //Cambiar la vista del carro y el obstáculo.
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
        //Cambiar la proyección. 8->perspectiva y 9->ortografica

        else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS){
            car.set_projection(8);
            obstacle.set_projection(8);
        }
        else if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS){
            car.set_projection(9);
            obstacle.set_projection(9);
        }
        
    } while ( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

    return 0;
}