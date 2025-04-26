#ifndef PLY_H
#define PLY_H

#pragma once

#include "Model.h"

class Ply:public Model{
public:
    Ply(string file_name);
    Ply();
    void set_file_name(string file_name);
private:
    void load(string file_name);
};
#endif