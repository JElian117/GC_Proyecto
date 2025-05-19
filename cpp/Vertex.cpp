#include "../include/Vertex.h"

/**
 * @brief Constructor de la clase Vertex:: Vertex object
 */
Vertex::Vertex(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

/**
 * @brief Constructor de la clase Vertex:: Vertex object
 * @param float x Coordenada x
 * @param float y Coordenada y
 * @param float z Coordenada z
 */
Vertex::Vertex(float x, float y, float z) //Implementación de la clase
{
    this->x = x; //anteponer el this->, ya que es un tema para distinguir que son los miembros de la clase
    this->y = y; //quitamos el new_ y el this y aparecen las confusiones de "x=x" y cosas así que pueden confundir
    this->z = z;
}

/**
 * @brief Método que imprime las coordenadas del objeto
 */
void Vertex::print()
{
    cout << "(" << x << "," << y << "," << z << ")" << endl;
}

/**
 * @brief Método para restar
 * @param Vertex op2 Operador restar
 */
Vertex Vertex::operator-(Vertex op2)
{
    float nx = this->x - op2.x;
    float ny = this->y - op2.y;
    float nz = this->z - op2.z;
    Vertex P(nx, ny, nz);

    return(P);
}

/**
 * @brief Método para sumar
 * @param Vertex op2 Operador sumar
 */
Vertex Vertex::operator+(Vertex op2)
{
    float nx = this->x + op2.x;
    float ny = this->y + op2.y;
    float nz = this->z + op2.z;
    Vertex P(nx, ny, nz);

    return(P);
}

/**
 * @brief Método para multiplicar
 * @param float op2 Operador multiplicar
 */
Vertex Vertex::operator*(float op2)
{
    float nx = this->x * op2;
    float ny = this->y * op2;
    float nz = this->z * op2;
    Vertex P(nx, ny, nz);

    return(P);
}

//Setters
/**
 * @brief Método setter que establece la coordenada x
 * @param float x Coordenada x
 */
void Vertex::set_x(float x)
{ 
    this->x = x;
}

/**
 * @brief Método setter que establece la coordenada y
 * @param float y Coordenada y
 */
void Vertex::set_y(float y)
{ 
    this->y = y;
}

/**
 * @brief Método setter que establece la coordenada z
 * @param float z Coordenada z
 */
void Vertex::set_z(float z)
{ 
    this->z = z;
}

//Getters
/**
 * @brief Método getter que regresa la coordenada x
 * @return float Coordenada x
 */
float Vertex::get_x()
{
    return this->x;
}

/**
 * @brief Método getter que regresa la coordenada y
 * @return float Coordenada y
 */
float Vertex::get_y()
{
    return this->y;
}

/**
 * @brief Método getter que regresa la coordenada z
 * @return float Coordenada z
 */
float Vertex::get_z()
{
    return this->z;
}

/**
 * @brief Método que regresa el octante al que pertenece el objeto
 */
void Vertex::octant(){
    string name;
    if(this->x >= 0 && this->y >= 0 && this->z >= 0)
        name = "I";
    if(this->x < 0 && this->y >= 0 && this->z >= 0)
        name = "II";
    if(this->x < 0 && this->y < 0 && this->z >= 0)
        name = "II";
    if(this->x >= 0 && this->y < 0 && this->z >= 0)
        name = "IV";
    if(this->x >= 0 && this->y >= 0 && this->z < 0)
        name = "V";
    if(this->x < 0 && this->y >= 0 && this->z < 0)
        name = "VI";
    if(this->x < 0 && this->y < 0 && this->z < 0)
        name = "VII";
    if(this->x >= 0 && this->y < 0 && this->z < 0)
        name = "VIII";

    cout<<"Octante: "<<name<<endl;
}

/**
 * @brief Método que regresa la matriz homogénea del objeto
 * @return arma::Col<float> Matriz homogénea
 */
arma::Col<float> Vertex::h(){
    arma::Col<float> hm = {this->x, this->y, this->z, 1};
    return hm;
}