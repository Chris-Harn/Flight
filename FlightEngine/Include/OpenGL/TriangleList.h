#ifndef __TRIANGLE_LIST__
#define __TRIANGLE_LIST__

#include <GL/glew.h>

class TriangleList {
public:
    TriangleList();
    ~TriangleList();

    void  CreateTriangleList( int width, int depth );
private:
    int m_width;
    int m_depth;
    GLuint m_VAO, m_VBO, m_IBO;
};

#endif
