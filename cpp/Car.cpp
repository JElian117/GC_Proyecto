// Creado por JElian117 el 26/04/25, última modificación: 09/05/25.
#define _USE_MATH_DEFINES

#include <math.h>
#include "../include/Car.h"

/**
 * @brief Constructor de la clase Car:: Car object
 * @param Vertex initial_pos Posición inicial del objeto
 * @param GLuint programID ID del programa de shader
 */
Car::Car (Vertex inital_pos, GLuint programID){
    Animation an;

    this->initial_pos = inital_pos;
    this->current_pos = inital_pos;

    // Inicializar velocidad, ángulo de dirección y estado de movimiento
    this->speed = 0.2f;
    this->steering_angle = 0.0f; // Ángulo de dirección inicial
    this->is_moving = false;
    this->move_index = 0;

    //this->transform = an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z())
    //Paso 1: Escalar. Paso 2: Rotar respecto de 'Y'. Paso 3: Trastadar respecto a 'X' un poco a la izquierda.
    //this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z()) *
    //                    an.Ry(90) * an.S(0.05, 0.05, 0.05);
    //Escalar y llevar a posición inicial                    
    this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z(), true) *
                        an.S(0.05, 0.05, 0.05, true);

    this->car.set_file_name("models/car.obj");
    this->car.set_transform(this->transform);
    this->car.set_color(1.0, 1.0, 1.0);
    this->car_data.set_data(this->car.get_vertex_buffer_data(), this->car.get_vertex_color_data());

    this->programID = programID;

    // Configurar ejes para rotación (delanteros)
    this->rotation_axis_p1 = Vertex(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z() - 0.5);
    this->rotation_axis_p2 = Vertex(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z() + 0.5);

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
 * @brief Método que establece la velocidad del carro
 * @param float inc Incremento o decremento de velocidad (positivo para acelerar, negativo para frenar)
 */
void Car::set_speed(float inc) {
    this->speed += inc;
    
    // Limitar velocidad máxima y mínima
    if(this->speed < 0.0f) this->speed = 0.0f;
    if(this->speed > 1.0f) this->speed = 1.0f;
    
    cout << "Velocidad: " << this->speed << endl;
}

/**
 * @brief Método que establece el ángulo de dirección del carro
 * @param float inc Incremento o decremento del ángulo de dirección (desde la perspectiva del carro: positivo para girar a la izquierda, negativo para girar a la derecha)
 */
void Car::set_steering(float inc) {
    this->steering_angle += inc;
    
    // Limitar ángulo de dirección
    if(this->steering_angle < -60.0f) this->steering_angle = -60.0f;
    if(this->steering_angle > 60.0f) this->steering_angle = 60.0f;
    
    cout << "Ángulo de dirección: " << this->steering_angle << endl;
}

/**
 * @brief Método que actualiza la posición del carro según su velocidad y ángulo de dirección
 */
void Car::update_position() {
    if(speed <= 0.0f) return;
    
    Animation an;
    
    // Punto actual
    Vertex P1(current_pos.get_x(), current_pos.get_y(), current_pos.get_z());
    
    // Vector tangente (dirección actual)
    Vertex R1(cos(steering_angle * M_PI / 180.0f), 0, sin(steering_angle * M_PI / 180.0f));
    R1 = R1 * speed;
    
    // Punto final estimado
    Vertex P4 = P1 + R1 * 2.0f; // Multiplicamos para extender la curva
    
    // Vector tangente final (misma dirección pero puede cambiar si hay volantazo)
    Vertex R4 = R1;
    
    // Generar curva de Hermite
    this->trajectory = an.move_hermite(P1, P4, R1, R4, 0.05f);
    this->is_moving = true;
    this->move_index = 0;
}

/**
 * @brief Método que dibuja el objeto Car
 */
void Car::draw(){
    Animation an;

    if(is_moving && move_index < trajectory.size()) {
        current_pos = trajectory[move_index];
        move_index++;
        
        if(move_index >= trajectory.size()) {
            is_moving = false;
        }
    }

    // Actualizar transformación
    this->transform = glm::mat4(1.0f);
    this->transform = an.T(current_pos.get_x(), current_pos.get_y(), current_pos.get_z(), true) *
                      an.Rp1p2(steering_angle, rotation_axis_p1, rotation_axis_p2, true) * an.S(0.05, 0.05, 0.05, true);
    
    this->car.set_transform(this->transform);
    this->car_data.draw(this->programID, this->projection * this->view * this->car.get_transform());
}

/**
 * @brief Método que obtiene la velocidad actual del carro
 * @return float Velocidad actual del carro
 */
float Car::get_speed() {
    return this->speed;
}

/**
 * @brief Método que resetea el estado del carro a su posición inicial y velocidad predeterminada
 */
void Car::reset() {
    this->current_pos = initial_pos;
    this->speed = 0.2f;
    this->steering_angle = 0.0f;
    this->is_moving = false;
    this->trajectory.clear();
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
    if(key == 8){
        this->projection = glm::perspective(
            glm::radians(45.0f), // Campo de visión vertical
            (float)1000 / (float)600, // Relación de aspecto
            0.1f, // Plano cercano
            10.0f // Plano lejano 
        );
    }
    else if(key == 9){
        this->projection = glm::ortho(
            -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f
        );
    }
}