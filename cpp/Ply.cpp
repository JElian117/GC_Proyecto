#include "../include/Ply.h"

/**
 * @brief Constructor de la clase Ply:: Ply object
 * @param string file_name Nombre del archivo
 */
Ply::Ply(string file_name):Model(file_name){
    this->load(file_name);
}

/**
 * @brief Constructor de la clase Ply:: Ply object
 */
Ply::Ply():Model(){

}

/**
 * @brief Método que establece el nombre del archivo
 * @param string file_name Nombre del archivo
 */
void Ply::set_file_name(string file_name){
    this->load(file_name);
}

/**
 * @brief Método que carga el archivo
 * @param string file_name Nombre del archivo
 */
void Ply::load(string file_name){
    string line;
    ifstream PLYfile(file_name);
    if (!PLYfile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << file_name << endl;
        return;
    }

    int num_vertices = 0, num_faces = 0;
    bool header = true;

    while (getline(PLYfile, line)) {
        vector<string> elems = split(line, ' ');
        if (elems.empty()) continue;

        if (header) {
            if (elems[0] == "element" && elems[1] == "vertex") {
                num_vertices = stoi(elems[2]);
            } else if (elems[0] == "element" && elems[1] == "face") {
                num_faces = stoi(elems[2]);
            } else if (elems[0] == "end_header") {
                header = false;
            }
        } else if (num_vertices > 0) {
                float x = stof(elems[0]);
                float y = stof(elems[1]);
                float z = stof(elems[2]);
                float nx = stof(elems[3]);
                float ny = stof(elems[4]);
                float nz = stof(elems[5]);
                vertices.push_back(Vertex(x, y, z));
                nvertices.push_back(Vertex(nx, ny, nz));
                num_vertices--;
        } else if (num_faces > 0) {
            vector<unsigned int> vs;
            for (unsigned int i = 1; i < elems.size(); i++) {
                vs.push_back(stoi(elems[i]));
            }
            faces.push_back(Face(vs));
            num_faces--;
        }
    }

    PLYfile.close();
}