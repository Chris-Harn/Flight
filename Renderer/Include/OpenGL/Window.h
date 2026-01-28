#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window {
public:
    Window();
    ~Window();
    bool Initialization( unsigned int width,
        unsigned int height,
        const char *title,
        bool fullScreen );
    void ClearColorBuffer();
    void SwapBuffers();
    void PollEvents();
    void Clean();
    bool *GetsKeys();
    bool IsKeyUp( int key );
    bool IsKeyDown( int key );
    bool GetShouldClose();
    float GetBufferWidth();
    float GetBufferHeight();
    GLfloat GetXChange();
    GLfloat GetYChange();
    GLFWwindow *GetWindow();
    void ToggleVsync( bool setVsync );
    void ToggleWireFrame( bool setWireFrame );
    bool GetVsync();

    enum PROTO {
        TOTAL_KEYS = 1024 /* Dev choosen number */
    };

    // Public Shared Variables
    GLfloat m_lastX;
    GLfloat m_lastY;
    GLfloat m_xChange;
    GLfloat m_yChange;
    bool m_bMouseFirstMove;

private:
    GLFWwindow *m_pWindow;
    bool m_bKeys[TOTAL_KEYS];
    int m_BufferWidth;
    int m_BufferHeight;
    bool m_vSync;

    // Callback function require static functions
    void CreateCallbacks();
    static void HandleKeys( GLFWwindow *window,
        int key,
        int code,
        int action,
        int mode );
    static void HandleMouse( GLFWwindow *window,
        double xPos,
        double yPos );
};

#endif