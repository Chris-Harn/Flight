#ifndef __MESH_H__
#define __MESH_H__

#include <GL/glew.h>

#include <glm/glm.hpp> // glm::vec2, glm::vec3, glm::mat4

class Mesh {
public:
    Mesh();
    ~Mesh();

    void CreateMesh( GLfloat *vertices, unsigned int numOfVertices );
    void RenderMesh();
    void Clean();

    glm::mat4 m_model; // Model Matrix

private:
    GLuint m_VAO, m_VBO;
    GLsizei m_indexCount;
};

#endif