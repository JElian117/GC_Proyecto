// Created by JElian117 on 26/04/25.

#include "../include/Obstacle.h"

/**
 * @brief Constructor de la clase Obstacle:: Obstacle object
 * @param Vertex initial_pos Posición inicial del objeto
 * @param GLuint programID ID del programa de shader
 */
Obstacle::Obstacle (Vertex inital_pos, GLuint programID){
    Animation an;

    this->initial_pos = inital_pos;

    //this->transform = an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z())
    //Paso 1: Escalar. Paso 2: Rotar respecto de 'Y'. Paso 3: Trastadar respecto a 'X' un poco a la izquierda.
    //this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z()) *
    //                    an.Ry(90) * an.S(0.05, 0.05, 0.05);
    //Escalar y llevar a posición inicial                    
    this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z(), true) *
                        an.S(0.05, 0.05, 0.05, true);

    this->person.set_file_name("models/person.obj");
    this->person.set_transform(this->transform);
    this->person.set_color(0.0, 0.0, 1.0);
    this->person_data.set_data(this->person.get_vertex_buffer_data(), this->person.get_vertex_color_data());

    this->cactus.set_file_name("models/cactus.ply");
    this->cactus.set_transform(this->transform);
    this->cactus.set_color(1.0, 0.0, 0.0);
    this->cactus_data.set_data(this->cactus.get_vertex_buffer_data(), this->cactus.get_vertex_color_data());

    this->programID = programID;

    this->view = glm::lookAt(
        glm::vec3(0, 0, 5), // Camera is at (0,0,5), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    //this->projection = glm::perspective(
    //    glm::radians(45.0f), // The vertical Field of View
    //    (float)1000 / (float)600, // Aspect Ratio
    //    0.1f, // Near clipping plane
    //    100.0f // Far clipping plane
    //); 
    this->projection = glm::ortho(
        -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f
    );
}

/**
 * @brief Método que dibuja el objeto Obstacle
 */
void Obstacle::draw(){
    Animation an;

    this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z(), true) *
                        an.S(0.05, 0.05, 0.05, true);

    this->person_data.draw(this->programID, this->projection * this->view * this->person.get_transform());
    this->cactus_data.draw(this->programID, this->projection * this->view * this->cactus.get_transform());
}

/**
 * @brief Método que establece la vista de la cámara
 * @param unsigned int key Tecla para cambiar la vista
 */
void Obstacle::set_view(unsigned int key){
    if(key == 1){
        this->view = glm::lookAt(
            glm::vec3(0, 0, 5), // Camera is at (0,0,5), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
    }
    else if(key == 2){
        this->view = glm::lookAt(
            glm::vec3(5, 5, 5), // Camera is at (5,5,5), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
    }
    else if(key == 3){
        this->view = glm::lookAt(
            glm::vec3(0, 0, 5), // Camera is at (0,5,0), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, -11, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
    }
    else if(key == 4){
        this->view = glm::lookAt(
            glm::vec3(5, 0, 5), // Camera is at (5,0,5), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
    }

}

/**
 * @brief Método que establece la proyección de la cámara
 * @param unsigned int key Tecla para cambiar la proyección
 */
void Obstacle::set_projection(unsigned int key){

}