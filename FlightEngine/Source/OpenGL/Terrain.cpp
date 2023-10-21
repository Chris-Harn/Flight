#include "OpenGL/Terrain.h"

Terrain::Terrain() {
    m_pterrainData = nullptr;
    m_terrainSize = 0;
}

Terrain::~Terrain() {
    if( m_pterrainData != nullptr ) {
        delete m_pterrainData;
        m_pterrainData = nullptr;
        m_terrainSize = 0;
    }
}

void Terrain::LoadFromArray( const char *pArray, int arraySize ) {

}

void Terrain::LoadFromArray( float *pArray, int arraySize ) {

}

