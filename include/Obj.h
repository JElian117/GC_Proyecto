#ifndef OBJ_H
#define OBJ_H

#pragma once

#include "Model.h"

class Obj:public Model{
public:
    Obj(string file_name);
    Obj();
    void set_file_name(string file_name);
private:
    void load(string file_name);
};
#endif