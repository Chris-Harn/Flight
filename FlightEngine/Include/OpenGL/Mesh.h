#ifndef __MESH_H__
#define __MESH_H__

#include <GL/glew.h>

#include <glm/glm.hpp> // glm::vec2, glm::vec3, glm::mat4

class Mesh {
public:
    Mesh();
    ~Mesh();

    void CreateMesh( GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices );
    void RenderMesh();
    void Clean();

    glm::mat4 m_model; // Model Matrix

private:
    GLuint m_VAO, m_VBO, m_IBO;
    GLsizei m_indexCount;
};

#endif