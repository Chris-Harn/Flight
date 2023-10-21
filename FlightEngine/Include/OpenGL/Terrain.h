#ifndef __TERRAIN__
#define __TERRAIN__

class Terrain {
public:
    Terrain();
    ~Terrain();

    void LoadFromArray( const char *pFilename, int arraySize );
private:
    unsigned char *m_pterrainData; // Height data
    int m_terrainSize; // Keep to a power of 2 in both directions
};

#endif