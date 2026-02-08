#ifndef __ENGINE_H__
#define __ENGINE_H__

class Shader;
class Mesh;
#include "OpenGL/Window.h"
#include "OpenGL/Camera.h"
#include "OpenGL/TextRenderer.h"
#include "Timer.h"

class Engine {
public:
    static Engine *Instance() {
        if( s_pInstance == 0 ) {
            s_pInstance = new Engine();
        }
        return s_pInstance;
    }

    bool Init();
    void HandleEvents();
    void Render();
    void Clean();
    bool Running();

private:
    Engine();
    ~Engine() {}

    static Engine *s_pInstance;

    // Controls
    bool m_bRunning;

public: 
    // OpenGL Items
    Window *m_pMainWindow;
    TextRenderer *m_pTextRenderer;
    Camera *m_pCamera;

    // Engine Systems
    Timer *m_pTimer;
};

typedef Engine TheEngine;

#endif