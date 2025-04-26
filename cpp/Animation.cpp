#define _USE_MATH_DEFINES

#include <math.h>
#include "../include/Animation.h"

Animation::Animation() {}

vector<Vertex> Animation::move_line(Vertex P1, Vertex P2, float dt){
    
    vector<Vertex> line = {};

    for(float t= 0.0f; t<=1.0f+dt; t+=dt) {
        line.push_back(P1 + ((P2 - P1) * t));
    }

    return(line);
}

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

arma::Mat<float>Animation::T(float dx,float dy,float dz){
    
    arma::Mat<float> T = {  {1, 0, 0, dx},
                            {0, 1, 0, dy},
                            {0, 0, 1, dz},
                            {0, 0, 0, 1} };

    return(T);
}

arma::Mat<float>Animation::S(float sx,float sy,float sz){

    arma::Mat<float> S = {  {sx, 0,  0,  0},
                            {0,  sy, 0,  0},
                            {0,  0,  sz, 0},
                            {0,  0,  0,  1} };
        
    return(S);
}

arma::Mat<float>Animation::Rx(float theta){

    float theta_eucli = theta * M_PI / 180;

    arma::Mat<float> Rx = { {1, 0,                0,                 0},
                            {0, cos(theta_eucli), -sin(theta_eucli), 0},
                            {0, sin(theta_eucli), cos(theta_eucli),  0},
                            {0, 0,                0,                 1} };

    return(Rx);
}

arma::Mat<float>Animation::Ry(float theta){

    float theta_eucli = theta * M_PI / 180;

    arma::Mat<float> Ry = { {cos(theta_eucli),  0, sin(theta_eucli), 0},
                            {0,                 1, 0,                0},
                            {-sin(theta_eucli), 0, cos(theta_eucli), 0},
                            {0,                 0, 0,                1} };

    return(Ry);
}

arma::Mat<float>Animation::Rz(float theta){

    float theta_eucli = theta * M_PI / 180;

    arma::Mat<float> Rz = { {cos(theta_eucli), -sin(theta_eucli), 0, 0},
                            {sin(theta_eucli), cos(theta_eucli),  0, 0},
                            {0,                0,                 1, 0},
                            {0,                0,                 0, 1} };

    return(Rz);
}

/*
Una rotación respecto a cualquier eje definiendo p1 y p2 como parte de posición de nuestro objeto.
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