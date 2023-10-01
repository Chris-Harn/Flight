#include "OpenGL/Mesh.h"


Mesh::Mesh() {
    m_VAO = 0;
    m_VBO = 0;
    m_IBO = 0;
    m_indexCount = 0;
    m_model = glm::mat4( 0.0f );
}

Mesh::~Mesh() {
    // Never clear OpenGL resources in deconstructor
}

void Mesh::CreateMesh( GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices ) {
    m_indexCount = numOfIndices;

    glGenVertexArrays( 1, &m_VAO );
    glBindVertexArray( m_VAO );

    glGenBuffers( 1, &m_IBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices[0] ) * numOfIndices, indices, GL_STATIC_DRAW );

    glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices[0] ) * numOfVertices, vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 0 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
}

void Mesh::RenderMesh() {
    glBindVertexArray( m_VAO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
    glDrawElements( GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0 );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
}

void Mesh::Clean() {
    if( m_VBO != 0 ) {
        glDeleteBuffers( 1, &m_VBO );
        m_VBO = 0;
    }

    if( m_IBO != 0 ) {
        glDeleteBuffers( 1, &m_IBO );
        m_IBO = 0;
    }

    if( m_VAO != 0 ) {
        glDeleteVertexArrays( 1, &m_VAO );
        m_VAO = 0;
    }

    m_indexCount = 0;
}