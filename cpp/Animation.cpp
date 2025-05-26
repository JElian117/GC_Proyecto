/*Creado por JElian117, última modificación: 07/05/25 */

#define _USE_MATH_DEFINES

#include <math.h>
#include "../include/Animation.h"

/** 
 *  @brief Constructor de la clase Animation:: Animation object
 */
Animation::Animation() {}

/**
 *  @brief Método que mueve una línea entre dos puntos P1 y P2.
 *  @param Vertex P1 Primer punto
 *  @param Vertex P2 Segundo punto
 *  @param float dt Delta diferencia
 *  @return vector <Vertex> de vértices que representan la línea
 */
vector<Vertex> Animation::move_line(Vertex P1, Vertex P2, float dt){
    
    vector<Vertex> line = {};

    for(float t= 0.0f; t<=1.0f+dt; t+=dt) {
        line.push_back(P1 + ((P2 - P1) * t));
    }

    return(line);
}

/**
 *  @brief Método que mueve una curva de Hermite entre dos puntos P1 y P4
 *  @param Vertex P1 Primer punto
 *  @param Vertex P4 Segundo punto
 *  @param Vertex R1 Primer vector tangente
 *  @param Vertex R4 Segundo vector tangente
 *  @param float dt Delta diferencia
 *  @return vector <Vertex> de vértices que representan la curva de Hermite
*/
vector<Vertex> Animation::move_hermite(Vertex P1, Vertex P4, Vertex R1, Vertex R4, float dt){
    
    vector<Vertex> curve= {};
    
    arma::Mat<float> MH = { {2, -2, 1, 1},
                            {-3, 3, -2, -1},
                            {0, 0, 1, 0},
                            {1, 0, 0, 0} };

    arma::Mat<float> GH = { { P1.get_x(), P1.get_y(), P1.get_z() }, 
                            { P4.get_x(), P4.get_y(), P4.get_z() }, 
                            { R1.get_x(), R1.get_y(), R1.get_z() }, 
                            { R4.get_x(), R4.get_y(), R4.get_z() } };

    for(float t=0.0; t<=1.0; t+=dt){ // 1.0 + dt?
        arma::Row<float> T = { powf(t, 3), powf(t, 2), t, 1 };
    
        arma::Mat<float> Qt = T * MH * GH;
    
        Vertex tv(Qt(0, 0), Qt(0, 1), Qt(0, 2));
        curve.push_back(tv);
    
        //cout << "t= " << t << endl << Qt << endl;
    }
    
    return(curve);
}

/**
 *  @brief Método que mueve una curva de Bezier entre cuatro puntos P1, P2, P3 y P4
 *  @param Vertex P1 Primer punto
 *  @param Vertex P2 Segundo punto
 *  @param Vertex P3 Tercer punto
 *  @param Vertex P4 Cuarto punto
 *  @param float dt Delta diferencia
 *  @return vector <Vertex> de vértices que representan la curva de Bezier
 */
vector<Vertex> Animation::move_bezier(Vertex P1, Vertex P2, Vertex P3, Vertex P4, float dt){
    
    vector<Vertex> curve= {};

    arma::Mat<float> MB = { { -1, 3, -3, 1 },
                            { 3, -6, 3, 0 },
                            { -3, 3, 0, 0 },
                            { 1, 0, 0, 0 } };

    arma::Mat<float> GB = { { P1.get_x(), P1.get_y(), P1.get_z() },
                            { P2.get_x(), P2.get_y(), P2.get_z() },
                            { P3.get_x(), P3.get_y(), P3.get_z() },
                            { P4.get_x(), P4.get_y(), P4.get_z() } };
    
    for (float t = 0.0; t <= 1.0+dt; t += dt) {
        arma::Row<float>T = {powf(t, 3), powf(t, 2), t, 1};
        arma::Mat<float>Qt = T * MB * GB; 

        Vertex tv(Qt(0,0), Qt(0, 1), Qt(0, 2));
        curve.push_back(tv);
    }
    
    return(curve);
}

/**
 * @brief Este método regresa una matriz traslación.
 * @param float dx 
 * @param float dy 
 * @param float dz 
 * @return Mat <float> 
 */
arma::Mat<float>Animation::T(float dx,float dy,float dz){
    
    arma::Mat<float> T = {  {1, 0, 0, dx},
                            {0, 1, 0, dy},
                            {0, 0, 1, dz},
                            {0, 0, 0, 1} };

    return(T);
}

/**
 * @brief Este método regresa una matriz de escalamiento.
 * @param float sx 
 * @param float sy 
 * @param float sz 
 * @return Mat <float> 
 */
arma::Mat<float>Animation::S(float sx,float sy,float sz){

    arma::Mat<float> S = {  {sx, 0,  0,  0},
                            {0,  sy, 0,  0},
                            {0,  0,  sz, 0},
                            {0,  0,  0,  1} };
        
    return(S);
}

/**
 * @brief Este método regresa una matriz de rotación respecto al eje X.
 * @param float theta 
 * @return Mat <float> 
 */
arma::Mat<float>Animation::Rx(float theta){

    float theta_eucli = theta * M_PI / 180;

    arma::Mat<float> Rx = { {1, 0,                0,                 0},
                            {0, cos(theta_eucli), -sin(theta_eucli), 0},
                            {0, sin(theta_eucli), cos(theta_eucli),  0},
                            {0, 0,                0,                 1} };

    return(Rx);
}

/**
 * @brief Este método regresa una matriz de rotación respecto al eje Y.
 * @param float theta 
 * @return Mat <float> 
 */
arma::Mat<float>Animation::Ry(float theta){

    float theta_eucli = theta * M_PI / 180;

    arma::Mat<float> Ry = { {cos(theta_eucli),  0, sin(theta_eucli), 0},
                            {0,                 1, 0,                0},
                            {-sin(theta_eucli), 0, cos(theta_eucli), 0},
                            {0,                 0, 0,                1} };

    return(Ry);
}

/**
 * @brief Este método regresa una matriz de rotación respecto al eje Z.
 * @param float theta 
 * @return Mat <float> 
 */
arma::Mat<float>Animation::Rz(float theta){

    float theta_eucli = theta * M_PI / 180;

    arma::Mat<float> Rz = { {cos(theta_eucli), -sin(theta_eucli), 0, 0},
                            {sin(theta_eucli), cos(theta_eucli),  0, 0},
                            {0,                0,                 1, 0},
                            {0,                0,                 0, 1} };

    return(Rz);
}


//Una rotación respecto a cualquier eje definiendo p1 y p2 como parte de posición de nuestro objeto.
/**
 * @brief Este método regresa una matriz de rotación respecto a un eje definido por dos puntos P1 y P2.
 * @param float theta 
 * @param Vertex P1 
 * @param Vertex P2 
 * @return Mat <float> 
 */
arma::Mat<float> Animation::Rp1p2(float theta, Vertex P1, Vertex P2){
    //Paso 1
    arma::Mat<float> T1 = this->T(-P1.get_x(), -P1.get_y(), -P1.get_z());
    //Paso 2
    float D1 = sqrt( powf(P2.get_z() - P1.get_z(), 2) + powf(P2.get_x() - P1.get_x(), 2) );
    arma::Mat<float> Ry2 = {{ (P2.get_z() - P1.get_z())/D1, 0, -(P2.get_x() - P1.get_x())/D1, 0},
                            { 0,                            1, 0,                             0},
                            { (P2.get_x() - P1.get_x())/D1, 0, (P2.get_z() - P1.get_z())/D1,  0},
                            { 0,                            0, 0,                             1} };
    //Paso 3
    float D2 = sqrt( powf(P2.get_z() - P1.get_z(), 2) + powf(P2.get_y() - P1.get_y(), 2) + powf(P2.get_x() - P1.get_x(), 2));
    arma::Mat<float> Rx3 = {{ 1,                            0, 0,                             0},
                            { 0,                        D1/D2, -(P2.get_y() - P1.get_y())/D2, 0},
                            { 0, (P2.get_y() - P1.get_y())/D2, D1/D2,                         0}, //Hay un caso en el que D1 o D2 puedan ser 0?
                            { 0,                            0, 0,                             1} };
    //Paso 4
    arma::Mat<float> Rz4 = this->Rz(theta);
    //Paso 5
    arma::Mat<float> Rx5 = Rx3.i(); //Usar la transpuesta podría ser mejor
    //Paso 6
    arma::Mat<float> Ry6 = Ry2.i(); //Usar la transpuesta podría ser mejor
    //Paso 7
    arma::Mat<float> T7 = T1.i();

    return( T7 * Ry6 * Rx5 * Rz4 * Rx3 * Ry2 * T1 );
}

/*Nuevos métodos, pero con glm 07/05/25
Realmente no importa el uso del bool, por lo que podría quitar el if*/
/**
 * @brief Este método regresa una matriz traslación usando glm.
 * @param float dx 
 * @param float dy 
 * @param float dz 
 * @return Mat <float> 
 */
glm::mat4 Animation::T(float dx,float dy, float dz, bool t){
    if(t)
        return glm::translate(glm::mat4(1.0f), glm::vec3(dx, dy, dz));
    else
        return glm::translate(glm::mat4(1.0f), glm::vec3(-dx, -dy, -dz));
}

/**
 * @brief Este método regresa una matriz de escalamiento usando glm.
 * @param float sx 
 * @param float sy 
 * @param float sz 
 * @return Mat <float> 
 */
glm::mat4 Animation::S(float sx,float sy, float sz, bool t){
    if(t)
        return glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, sz));
    else
        return glm::scale(glm::mat4(1.0f), glm::vec3(1/sx, 1/sy, 1/sz));
}

/**
 * @brief Este método regresa una matriz de rotación respecto al eje X usando glm.
 * @param float theta 
 * @return Mat <float> 
 */
glm::mat4 Animation::Rx(float theta, bool t){
    if(t)
        return glm::rotate(glm::mat4(1.0f), glm::radians(theta), glm::vec3(1, 0, 0));
    else
        return glm::rotate(glm::mat4(1.0f), glm::radians(-theta), glm::vec3(1, 0, 0));
}

/**
 * @brief Este método regresa una matriz de rotación respecto al eje Y usando glm.
 * @param float theta 
 * @return Mat <float> 
 */
glm::mat4 Animation::Ry(float theta, bool t){
    if(t)
        return glm::rotate(glm::mat4(1.0f), glm::radians(theta), glm::vec3(0, 1, 0));
    else
        return glm::rotate(glm::mat4(1.0f), glm::radians(-theta), glm::vec3(0, 1, 0));
}

/**
 * @brief Este método regresa una matriz de rotación respecto al eje Z usando glm.
 * @param float theta 
 * @return Mat <float> 
 */
glm::mat4 Animation::Rz(float theta, bool t){
    if(t)
        return glm::rotate(glm::mat4(1.0f), glm::radians(theta), glm::vec3(0, 0, 1));
    else
        return glm::rotate(glm::mat4(1.0f), glm::radians(-theta), glm::vec3(0, 0, 1));
}

/**
 * @brief Este método regresa una matriz de rotación respecto a un eje definido por dos puntos P1 y P2 usando glm.
 * @param float theta 
 * @param Vertex P1 
 * @param Vertex P2 
 * @return Mat <float> 
 */
glm::mat4 Animation::Rp1p2(float theta, Vertex P1, Vertex P2, bool t) {
    //Paso 1: Trasladar P1 al origen
    glm::mat4 T1 = this->T(-P1.get_x(), -P1.get_y(), -P1.get_z(), true);

    //Paso 2: Rotar alrededor de Y para alinear el eje con Z
    float dx = P2.get_x() - P1.get_x();
    float dy = P2.get_y() - P1.get_y();
    float dz = P2.get_z() - P1.get_z();
    float D1 = sqrtf(dz * dz + dx * dx);

    glm::mat4 Ry2(1.0f);
    if (D1 != 0.0f) {
        Ry2 = glm::mat4(
            (dz / D1), 0, -(dx / D1), 0,
            0,         1, 0,          0,
            (dx / D1), 0, (dz / D1),  0,
            0,         0, 0,          1
        );
    }

    //Paso 3: Rotar alrededor de X para alinear el eje con Y
    float D2 = sqrtf(dx * dx + dy * dy + dz * dz);

    glm::mat4 Rx3(1.0f);
    if (D2 != 0.0f) {
        Rx3 = glm::mat4(
            1, 0, 0, 0,
            0, D1 / D2, -(dy / D2), 0,
            0, (dy / D2), D1 / D2, 0,
            0, 0, 0, 1
        );
    }

    //Paso 4: Rotar alrededor de Z el ángulo theta
    glm::mat4 Rz4 = this->Rz(theta, true);

    //Paso 5: Deshacer rotación X
    glm::mat4 Rx5 = glm::inverse(Rx3);

    //Paso 6: Deshacer rotación Y
    glm::mat4 Ry6 = glm::inverse(Ry2);

    //Paso 7: Deshacer traslación
    glm::mat4 T7 = this->T(-P1.get_x(), -P1.get_y(), -P1.get_z(), false);

    glm::mat4 result = T7 * Ry6 * Rx5 * Rz4 * Rx3 * Ry2 * T1;

    //Si t es false, invertir la transformación (usar la inversa)
    if (!t)
        result = glm::inverse(result);

    return result;
}