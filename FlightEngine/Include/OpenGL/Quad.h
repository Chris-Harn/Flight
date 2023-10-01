#ifndef __QUAD__
#define __QUAD__

class Quad {
public:
    Quad();
    ~Quad();
    void RenderQuad();
    void Clean();

private:
    unsigned int m_VAO, m_VBO, m_IBO;
    int m_indexCount;
    int m_numOfIndices;
    int m_numOfVertices;
};

#endif
