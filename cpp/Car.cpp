// Creado por JElian117 el 26/04/25, última modificación: 09/05/25.

#include "../include/Car.h"

/**
 * @brief Constructor de la clase Car:: Car object
 * @param Vertex initial_pos Posición inicial del objeto
 * @param GLuint programID ID del programa de shader
 */
Car::Car (Vertex inital_pos, GLuint programID){
    Animation an;

    this->initial_pos = inital_pos;

    //this->transform = an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z())
    //Paso 1: Escalar. Paso 2: Rotar respecto de 'Y'. Paso 3: Trastadar respecto a 'X' un poco a la izquierda.
    //this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z()) *
    //                    an.Ry(90) * an.S(0.05, 0.05, 0.05);
    //Escalar y llevar a posición inicial                    
    this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z(), true) *
                        an.S(0.05, 0.05, 0.05, true);

    this->car.set_file_name("models/car2.obj");
    this->car.set_transform(this->transform);
    this->car.set_color(1.0, 1.0, 1.0);
    this->car_data.set_data(this->car.get_vertex_buffer_data(), this->car.get_vertex_color_data());

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
 * @brief Método que dibuja el objeto Car
 */
void Car::draw(){
    Animation an;

    this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z(), true) *
                        an.S(0.05, 0.05, 0.05, true);

    this->car_data.draw(this->programID, this->projection * this->view * this->car.get_transform());
}

/**
 * @brief Método que establece la vista de la cámara
 * @param unsigned int key Tecla para cambiar la vista
 */
void Car::set_view(unsigned int key){
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
void Car::set_projection(unsigned int key){

}