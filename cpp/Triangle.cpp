#include "../include/Triangle.h"

/**
 * @brief Constructor de la clase Triangle:: Triangle object
 */
Triangle::Triangle()
{

}

/**
 * @brief Constructor de la clase Triangle:: Triangle object
 * @param vector <GLfloat> vertex_buffer_data Datos de los vértices
 * @param vector <GLfloat> color_buffer_data Datos de los colores
 */
Triangle::Triangle(vector <GLfloat> vertex_buffer_data, vector <GLfloat> color_buffer_data)
{
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &this->vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(GLfloat), &vertex_buffer_data[0], GL_STATIC_DRAW);
	this->datasize = vertex_buffer_data.size();

	glGenBuffers(1, &this->colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size()*sizeof(GLfloat), &color_buffer_data[0], GL_STATIC_DRAW);
}

/**
 * @brief Método que establece los datos del objeto
 * @param vector <GLfloat> vertex_buffer_data Datos de los vértices
 * @param vector <GLfloat> color_buffer_data Datos de los colores
 */
void Triangle::set_data(vector <GLfloat> vertex_buffer_data, vector <GLfloat> color_buffer_data)
{
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &this->vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(GLfloat), &vertex_buffer_data[0], GL_STATIC_DRAW);
	this->datasize = vertex_buffer_data.size();

	glGenBuffers(1, &this->colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size()*sizeof(GLfloat), &color_buffer_data[0], GL_STATIC_DRAW);    
}

/**
 * @brief Método que dibuja el objeto
 * @param GLuint programID ID del programa de shader
 * @param glm::mat4 mvp Matriz de transformación
 */
void Triangle::draw(GLuint programID, glm::mat4 mvp)
{
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, this->datasize); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}