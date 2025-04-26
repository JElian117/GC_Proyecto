#define _USE_MATH_DEFINES

#include <math.h>
#include "../include/Cannon.h"

Cannon::Cannon (Vertex inital_pos){
    Animation an;

    this->initial_pos = inital_pos;
    this->angle = 0.0;
    this->force = 0.6;

    //Si era correcto, solo necesitaba unas modificaciones
    this->E1.set_x(initial_pos.get_x()+0.01);
    this->E1.set_y(initial_pos.get_y()+0.01);
    this->E1.set_z(initial_pos.get_z()-1.0); //Modifiqué este valor para que funcionara la rotación p1p2

    this->E2.set_x(initial_pos.get_x()+0.01);
    this->E2.set_y(initial_pos.get_y()+0.01);
    this->E2.set_z(initial_pos.get_z()+1.0); //Modifiqué este valor para que funcionara la rotación p1p2


    //this->transform = an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z())
    //Paso 1: Escalar. Paso 2: Rotar respecto de 'Y'. Paso 3: Trastadar respecto a 'X' un poco a la izquierda.
    //this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z()) *
    //                    an.Ry(90) * an.S(0.05, 0.05, 0.05);
    //Escalar y llevar a posición inicial                    
    this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z()) *
                        an.S(0.05, 0.05, 0.05);

    this->body.set_file_name("Models/car.obj");
    this->body.set_transform(this->transform);
    this->body.set_color(1.0, 1.0, 1.0);

    this->bullet.set_file_name("Models/person.obj");
    //this->bullet.set_transform(an.T(-0.2, 0.0, 0.0) * this->transform);
    this->bullet.set_transform(this->transform);
    this->bullet.set_color(0.0, 0.0, 1.0);

    this->l_wheel.set_file_name("Models/cactus.ply");
    this->l_wheel.set_transform(this->transform);
    this->l_wheel.set_color(1.0, 0.0, 0.0);


    //this->transform = an.T(inital_pos.get_x(), inital_pos.get_y(), inital_pos.get_z()); //Creo que esto es lo que me provocó problemas con el body en draw.
    this->trajectory = {};
    this->shooted = false;
    this->i_shoot = 0;
}

void Cannon::set_angle(float inc){ //No es necesario un getter? Para usarlo por ejemplo así: cannon.set_angle(cannon.get_angle() + 1);

    this->angle += inc;

    if(this->angle < 0.0)
        this->angle = 0.0;
    if(this->angle > 90.0)
        this->angle = 90.0;
    
    //cout << "Angulo: " << this->angle << endl;
    //this->body.set_transform(an.Rz(this->angle));
}

void Cannon::set_force(float inc){
    this->force += inc;
    cout << "Fuerza: " << this->force << endl;

    if(this->force < 0.0)
        this->force = 0.0;
    if(this->force > 2.0)
        this->force = 2.0;
}

void Cannon::shoot(){
    Animation an;
    
    Vertex P1(this->initial_pos.get_x()+0.01, this->initial_pos.get_y()+0.01, 0);
    float ang = this->angle * (M_PI / 180);
    Vertex P2(P1.get_x()+this->force, P1.get_y()+(1-cos(ang)), 0);
    Vertex P3(P2.get_x()+this->force, P2.get_y(), 0);
    Vertex P4(P3.get_x()+this->force, 0, 0);

    this->trajectory = an.move_bezier(P1, P2, P3, P4, 0.01);
    this->shooted = true;
}

void Cannon::draw(){
    Animation an;

    /*
    Por alguna razón tuve que volver a definir la transformación aquí (Ya estaba en el constructor)
    Ya que aparecía el objeto de body gigante en toda la pantalla.
    Ahora si aparece como debería.
    FIXED: Agregué esta transformación y cosas raras comenzaron a pasar con como se dibujaba el obj.
    NOTA: Creo que es porque arriba definí por accidente nuevamente la transformación
    */
    this->transform =   an.T(initial_pos.get_x(), initial_pos.get_y(), initial_pos.get_z()) *
                        an.S(0.05, 0.05, 0.05);

    //Al ser matrices si afecta el orden de los factores, se veía al revés porque el profe puso en an.Rp2p2 primero.
    this->body.set_transform(this->transform * an.Rp1p2(this->angle, E1, E2));
    //this->body.set_transform(this->transform * an.Rz(this->angle));

    this->body.draw();
    this->l_wheel.draw();
    this->r_wheel.draw();

    if(this->shooted){
        float tx = this->trajectory[this->i_shoot].get_x();
        float ty = this->trajectory[this->i_shoot].get_y();
        float tz = this->trajectory[this->i_shoot].get_z();
        this->bullet.set_transform(an.T(tx, ty, tz) * this->transform);
        if(i_shoot < this->trajectory.size()-1){
            i_shoot++;
        }
        if(i_shoot == this->trajectory.size()-1){
            this->shooted = false;
        }
    }

    this->bullet.draw();
}


void Cannon::reset(){
    cout << "RESET" << endl;
    this->trajectory.clear();
    this->shooted = false;
    this->bullet.set_transform(this->transform);
}