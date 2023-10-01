#ifndef __ENGINE_H__
#define __ENGINE_H__

class Window;
class Camera;
class TextRenderer;
class Quad;
class Shader;
class Mesh;
class Timer;

class Engine {
public:
    static Engine *Instance() {
        if( s_pInstance == 0 ) {
            s_pInstance = new Engine();
        }
        return s_pInstance;
    }

    bool Init( const char *title, int windowWidth, int windowHeight, bool fullScreen );
    void HandleEvents();
    void Render();
    void Clean();
    bool Running();
private:
    Engine();
    ~Engine() { }
    
    static Engine *s_pInstance;

    // Simple Controls
    bool m_bRunning;
    bool m_bDisplayText;

    // OpenGL Items
    Window *m_pMainWindow;
    TextRenderer *m_pTextRenderer;
    Camera *m_pCamera;
    Quad *m_pQuad;

    // Engine Items
    Timer *m_pTimer;

    // Temp OpenGL Resources
    Mesh *m_pTerran;
    Mesh *m_pTerran2;
    Mesh *m_pTerran3;
    //Shader *m_pBlitImageToScreenShader;
    //Shader *m_pBlitTextToScreenShader;
};

typedef Engine TheEngine;

#endif