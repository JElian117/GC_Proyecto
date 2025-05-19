#ifndef OBJ_H
#define OBJ_H

#pragma once

#include "Model.h"

/**
 * * @brief Esta clase es usada para crear objetos usando un archivo obj. Clase Obj:: Obj object
 */
class Obj:public Model{
public:
    Obj(string file_name);
    Obj();
    void set_file_name(string file_name);
private:
    void load(string file_name);
};
#endif