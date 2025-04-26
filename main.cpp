#include <iostream>
#include "include/Vertex.h"
#include "include/Cannon.h"
#include "include/OpenGL.h"
#include "include/Triangle.h"

using namespace std;

int main(){
    Vertex initial_pos(-0.8, 0, 0);
    Cannon cannon(initial_pos);
    cout<<"Cañon cargado con exito"<<endl;

    OpenGL gl = OpenGL();

    GLFWwindow *window = gl.createWindow(1000, 600, "Cannon");
    if( window == NULL )
        return -1;

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    //cannon.set_angle(45);
    //cannon.set_force(2);
    //cout<<"Disparado con un angulo de 45 y fuerza de 2"<<endl;
    //cannon.shoot();
    //cout<<"Disparo terminado"<<endl;
    Triangle tr1({-1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -0.5f, 0.0f, 0.0f,
                0.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f, 0.0f, 0.0f,
                -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
                {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f});

    glClearColor(0.0f, 0.0f, 0.0f ,0.0f);

    bool release_up = true;
    bool release_down = true;
    bool release_space = true;
    bool release_r = true;
    bool release_right = true;
    bool release_left = true;
    do {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        cannon.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

        int state_up = glfwGetKey(window, GLFW_KEY_UP);
        int state_down = glfwGetKey(window, GLFW_KEY_DOWN);
        int state_space = glfwGetKey(window, GLFW_KEY_SPACE);
        int state_r = glfwGetKey(window, GLFW_KEY_R);
        int state_right = glfwGetKey(window, GLFW_KEY_RIGHT);
        int state_left = glfwGetKey(window, GLFW_KEY_LEFT);
        
        if(state_up == GLFW_PRESS && release_up){
            release_up = false;
            //cout << "Tecla arriba" << endl;
            cannon.set_angle(5.0);
        }
        if(state_up == GLFW_RELEASE ){
            release_up = true;
        }

        if(state_down == GLFW_PRESS && release_down){
            release_down = false;
            cannon.set_angle(-5.0);
            //cout << "Tecla abajo" << endl;
            //cannon.set_angle(cannon.get_angle() - 1);
        }
        if(state_down == GLFW_RELEASE ){
            release_down = true;
        }

        if(state_space == GLFW_PRESS && release_space){
            release_space = false;
            cannon.shoot();
            //cout<<"Disparo terminado (Barra espaciadora)"<<endl;
        }
        if(state_space == GLFW_RELEASE ){
            release_space = true;
        }
        
        if(state_r == GLFW_PRESS && release_r){
            release_r = false;
            cannon.reset();
            //cout<<"Disparo terminado (Barra espaciadora)"<<endl;
        }
        if(state_r == GLFW_RELEASE ){
            release_r = true;
        }
        
        if(state_right == GLFW_PRESS && release_right){
            release_right = false;
            cannon.set_force(0.1);
        }
        if(state_right == GLFW_RELEASE ){
            release_right = true;
        }
        
        if(state_left == GLFW_PRESS && release_left){
            release_left = false;
            cannon.set_force(-0.1);
        }
        if(state_left == GLFW_RELEASE ){
            release_left = true;
        }

    } while ( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
    glfwWindowShouldClose(window) == 0 );

    return 0;
}