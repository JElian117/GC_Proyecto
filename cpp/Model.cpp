#include "../include/Model.h"

Model::Model(string file_name){
    this->faces = {};
    this->vertices = {};
    this->transform = { (1, 0, 0, 0),
                        (0, 1, 0, 0),
                        (0, 0, 1, 0),
                        (0, 0, 0, 1)};
    this->r = 0.0f;
    this->g = 0.0f;
    this->b = 0.0f;
}

Model::Model(){
    this->faces = {};
    this->vertices = {};
    this->transform = { (1, 0, 0, 0),
                        (0, 1, 0, 0),
                        (0, 0, 1, 0),
                        (0, 0, 0, 1)};
    this->r = 0.0f;
    this->g = 0.0f;
    this->b = 0.0f;
}

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

void Model::print(){
    for(unsigned int ind_face = 0; ind_face < this->faces.size(); ind_face++){
        cout<<"Cara "<<ind_face+1<<endl;
        for(unsigned int iv = 0; iv <this->faces[ind_face].get_vertices().size(); iv++){
            unsigned int ind_v = this->faces[ind_face].get_vertices()[iv];
            this->vertices[ind_v].print();
        }
    }
}

void Model::set_transform(arma::Mat<float> transform){
    this->transform = transform;
}

void Model::set_color(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
}

void Model::draw(){
    vector<GLfloat> vertex_data = {};
    vector<GLfloat> vertex_color = {};
    
    for(Face f:this->faces){
        for(unsigned int iv: f.get_vertices()){
            arma::Mat<float> v = this->transform * this->vertices[iv].h();
            
            vertex_data.push_back(v.at(0, 0));
            vertex_data.push_back(v.at(1, 0));
            vertex_data.push_back(v.at(2, 0));
            vertex_color.push_back(this->r);
            vertex_color.push_back(this->g);
            vertex_color.push_back(this->b);
        }
    }
    Triangle tr1(vertex_data , vertex_color);
    tr1.draw();
}