#ifndef __ENGINE_H__
#define __ENGINE_H__

class Window;
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
    ~Engine() {}

    static Engine *s_pInstance;

    // Controls
    bool m_bRunning;

    // Renderer
    Window *m_pMainWindow;

    // Systems

    Timer *m_pTimer;
};

typedef Engine TheEngine;

#endif