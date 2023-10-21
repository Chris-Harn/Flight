#include "OpenGL/Terrain.h"

Terrain::Terrain() {
    m_pWaterData = nullptr;
    m_terrainSize = 0;
}

Terrain::~Terrain() {
    if( m_pWaterData != nullptr ) {
        delete m_pWaterData;
        m_pWaterData = nullptr;
        m_terrainSize = 0;
    }
}

void Terrain::LoadFromArray( const char *pArray, int arraySize ) {

}

void Terrain::LoadFromArray( float *pArray, int arraySize ) {

}

