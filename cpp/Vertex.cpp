#include "../include/Vertex.h"

Vertex::Vertex(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vertex::Vertex(float x, float y, float z) //Implementación de la clase
{
    this->x = x; //anteponer el this->, ya que es un tema para distinguir que son los miembros de la clase
    this->y = y; //quitamos el new_ y el this y aparecen las confusiones de "x=x" y cosas así que pueden confundir
    this->z = z;
}

void Vertex::print()
{
    cout << "(" << x << "," << y << "," << z << ")" << endl;
}

Vertex Vertex::operator-(Vertex op2)
{
    float nx = this->x - op2.x;
    float ny = this->y - op2.y;
    float nz = this->z - op2.z;
    Vertex P(nx, ny, nz);

    return(P);
}

Vertex Vertex::operator+(Vertex op2)
{
    float nx = this->x + op2.x;
    float ny = this->y + op2.y;
    float nz = this->z + op2.z;
    Vertex P(nx, ny, nz);

    return(P);
}

Vertex Vertex::operator*(float op2)
{
    float nx = this->x * op2;
    float ny = this->y * op2;
    float nz = this->z * op2;
    Vertex P(nx, ny, nz);

    return(P);
}

//Setters
void Vertex::set_x(float x)
{ 
    this->x = x;
}
void Vertex::set_y(float y)
{ 
    this->y = y;
}
void Vertex::set_z(float z)
{ 
    this->z = z;
}

//Getters
float Vertex::get_x()
{
    return this->x;
}

float Vertex::get_y()
{
    return this->y;
}

float Vertex::get_z()
{
    return this->z;
}

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

arma::Col<float> Vertex::h(){
    arma::Col<float> hm = {this->x, this->y, this->z, 1};
    return hm;
}