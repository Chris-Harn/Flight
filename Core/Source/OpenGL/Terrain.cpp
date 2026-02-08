#include "OpenGL/Terrain.h"

#include <GL/glew.h>

#include <vector>

Terrain::Terrain() {
    m_VAO = 0;
    m_VBO = 0;
}

Terrain::~Terrain() {

}

void Terrain::LoadFromArray( unsigned char *pArray, int arraySize ) {
    // Prepare data to load onto the GPU
    std::vector<unsigned char> vertices;
    float yScale = 64.0f / 256.0f, yShift = 16.0f; // Apply a scale + shift to the height data
    for( unsigned int i = 0; i < arraySize; i++ ) {
        for( unsigned int j = 0; j < arraySize; j++ ) {
            unsigned char *texel = &pArray[0] + ( j + arraySize * i );
            unsigned char y = texel[0];

            vertices.push_back( -arraySize / 2.0f + i );        // v.x
            vertices.push_back( (int)y * yScale - yShift );     // v.y
            vertices.push_back( -arraySize / 2.0f + j );        // v.z
        }
    }

    // Now load the data on the GPU
    glGenVertexArrays( 1, &m_VAO );
    glBindVertexArray( m_VAO );

    glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( Vertex ), &vertices[0], GL_STATIC_DRAW );

    // Vertex Position
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void *)0 );

    glBindVertexArray( 0 );
}

void Terrain::LoadFromArray( float *pArray, int arraySize ) {

}

void Terrain::Clean() {

}

