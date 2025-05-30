#include "../include/Obj.h"

/**
 * @brief Constructor de la clase Obj:: Obj object
 * @param string file_name Nombre del archivo
 */
Obj::Obj(string file_name):Model(file_name)
{
    this->load(file_name);
}

/**
 * @brief Constructor de la clase Obj:: Obj object
 */
Obj::Obj():Model(){

}

/**
 * @brief Método que establece el nombre del archivo
 * @param string file_name Nombre del archivo
 */
void Obj::set_file_name(string file_name){
    this->load(file_name);
}

/**
 * @brief Método que carga el archivo
 * @param string file_name Nombre del archivo
 */
void Obj::load(string file_name){
    string line;
    ifstream OBJfile(file_name);
    if (!OBJfile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << file_name << endl;
        return;
    }

    while (getline(OBJfile, line))
    {
        istringstream iss(line);
        vector<string> elements;
        string token;
        while (iss >> token) {
            elements.push_back(token);
        }

        if (!elements.empty()) {
            if (elements[0] == "v" && elements.size() >= 4) {
                float x = stof(elements[1]);
                float y = stof(elements[2]);
                float z = stof(elements[3]);
                vertices.push_back(Vertex(x, y, z));
            }
            if (elements[0] == "vn" && elements.size() >= 4) {
                float a = stof(elements[1]);
                float b = stof(elements[2]);
                float c = stof(elements[3]);
                nvertices.push_back(Vertex(a, b, c));
            }
            if (elements[0] == "f") {
                vector<unsigned int> vs = {};
                for (unsigned int i = 1; i < elements.size(); i++) {
                    vs.push_back(stoi(split(elements[i], '/')[0]) - 1);
                }
                faces.push_back(Face(vs));
            }
        }
    }

    OBJfile.close();
}