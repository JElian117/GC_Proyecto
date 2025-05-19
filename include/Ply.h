#ifndef PLY_H
#define PLY_H

#pragma once

#include "Model.h"

/**
 * * @brief Esta clase es usada para crear objetos usando un archivo ply. Clase Ply:: Ply object
 */
class Ply:public Model{
public:
    Ply(string file_name);
    Ply();
    void set_file_name(string file_name);
private:
    void load(string file_name);
};
#endif