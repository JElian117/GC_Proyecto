#include "../include/Model.h"

/**
 * @brief Constructor de la clase Model:: Model object
 * @param string file_name Nombre del archivo
 */
Model::Model(string file_name){
    this->faces = {};
    this->vertices = {};
    this->model = glm::mat4(1.0f);
    this->r = 0.0f;
    this->g = 0.0f;
    this->b = 0.0f;
}

/**
 * @brief Constructor de la clase Model:: Model object
 */
Model::Model(){
    this->faces = {};
    this->vertices = {};
    this->model = glm::mat4(1.0f);
    this->r = 0.0f;
    this->g = 0.0f;
    this->b = 0.0f;
}

/**
 * @brief Método que carga el archivo
 * @param string file_name Nombre del archivo
 * @param delim Delimitador
 * @return vector<string> Vértices del objeto
 */
vector<string> Model::split(const string& org_str, const char& delim){
    vector<string> str_array;
    stringstream ss(org_str);
    string t;
    while (getline(ss, t, delim)) {
        if (!t.empty()) 
            str_array.push_back(t);
    }
    if (str_array.empty())
        str_array.push_back(org_str);
    return str_array;
}

/**
 * @brief Método que imprime los vértices del objeto
 */
void Model::print(){
    for(unsigned int ind_face = 0; ind_face < this->faces.size(); ind_face++){
        cout<<"Cara "<<ind_face+1<<endl;
        for(unsigned int iv = 0; iv <this->faces[ind_face].get_vertices().size(); iv++){
            unsigned int ind_v = this->faces[ind_face].get_vertices()[iv];
            this->vertices[ind_v].print();
        }
    }
}

/**
 * @brief Método setter que establece la matriz de transformación
 * @param glm::mat4 transform Matriz de transformación
 */
void Model::set_transform(glm::mat4 transform){
    this->model = transform;
}

/**
 * @brief Método setter que establece el color del objeto
 * @param float r Componente roja
 * @param float g Componente verde
 * @param float b Componente azul
 */
void Model::set_color(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
}

/**
 * @brief Método getter que regresa la matriz de transformación
 * @return glm::mat4 Matriz de transformación
 */
glm::mat4 Model::get_transform(){
    return this->model;
}

/**
 * @brief Método que regresa los datos de los vértices
 * @return vector<GLfloat> Datos de los vértices
 */
vector<GLfloat> Model::get_vertex_buffer_data()
{
    vector<GLfloat> vertex_data = {};

    for(Face f:this->faces){
        for(unsigned int iv: f.get_vertices()){
            vertex_data.push_back(this->vertices[iv].get_x());
            vertex_data.push_back(this->vertices[iv].get_y());
            vertex_data.push_back(this->vertices[iv].get_z());
        }
    }
    return vertex_data;
}

/**
 * @brief Método que regresa los datos de los colores de los vértices
 * @return vector<GLfloat> Datos de los colores de los vértices
 */
vector<GLfloat> Model::get_vertex_color_data()
{
    vector<GLfloat> vertex_color = {};

    for(Face f:this->faces){
        for(unsigned int iv: f.get_vertices()){
            vertex_color.push_back(this->r);
            vertex_color.push_back(this->g);
            vertex_color.push_back(this->b);
        }
    }
    return vertex_color;
}