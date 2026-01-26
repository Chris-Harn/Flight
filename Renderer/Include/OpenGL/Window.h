#ifndef __WINDOW_H__
#define __WINDOW_H__

struct GLFWwindow;

enum protoWindow {
    TOTAL_KEYS = 1024 /* Dev choosen number */
};

class Window {
public:
    Window();
    ~Window();
    bool Initialize( unsigned int width,
        unsigned int height,
        const char *title,
        bool fullScreen );
    void PollEvents();
    void ClearColorBuffer();
    void UpscaleImage();
    void SwapBuffer();
    bool GetShouldClose();
    void Clean();

    bool *GetsKeys();
    GLFWwindow *GetWindow();
private:
    GLFWwindow *m_pMainWindow;
    bool m_bKeys[TOTAL_KEYS];

    int m_bufferWidth, m_bufferHeight;

    void CreateCallbacks();
    static void HandleKeys( GLFWwindow *window,
        int key,
        int code,
        int action,
        int mode );
};

#endif