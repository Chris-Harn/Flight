#include "OpenGL/Mesh.h"

#include <iostream>

Mesh::Mesh() {
    m_VAO = 0;
    m_VBO = 0;
    m_indexCount = 0;
    m_model = glm::mat4( 0.0f );
}

Mesh::~Mesh() {
    // Never clear OpenGL resources in deconstructor
}

void Mesh::CreateMesh( GLfloat *vertices, unsigned int numOfVertices ) {
    m_indexCount = numOfVertices;

    glGenVertexArrays( 1, &m_VAO );
    glBindVertexArray( m_VAO );

    glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices[0] ) * numOfVertices, vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), (void *)0 );
    glEnableVertexAttribArray( 0 ); // VertexPosition

    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), (void *)( 3 * sizeof( float ) ) );
    glEnableVertexAttribArray( 1 ); // VertexNormal

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
}

void Mesh::RenderMesh() {
    glBindVertexArray( m_VAO );
    glDrawArrays( GL_TRIANGLES, 0, m_indexCount );
    glBindVertexArray( 0 );
}

void Mesh::Clean() {
    if( m_VBO != 0 ) {
        glDeleteBuffers( 1, &m_VBO );
        m_VBO = 0;
    }

    if( m_VAO != 0 ) {
        glDeleteVertexArrays( 1, &m_VAO );
        m_VAO = 0;
    }

    m_indexCount = 0;
}