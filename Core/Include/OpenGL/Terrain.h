#ifndef __TERRAIN__
#define __TERRAIN__

#include <glm/glm.hpp> // glm::vec2, glm::vec3, glm::mat4

struct Vertex {
    glm::vec3 Position;
};

class Terrain {
public:
    Terrain();
    ~Terrain();

    void LoadFromArray( unsigned char *pArray, int arraySize );
    void LoadFromArray( float *pArray, int arraySize );
    void Clean();

private:
    unsigned int m_VAO, m_VBO;
};

#endif