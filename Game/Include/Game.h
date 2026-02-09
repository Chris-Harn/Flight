#ifndef __GAME__
#define __GAME__

#define VERSION "0.0.2"

#ifdef NDEBUG
    #define TITLE "Flight"
    #define RENDER_X_RESOLUTION 1920
    #define RENDER_Y_RESOLUTION 1080
    #define FULL_SCREEN true
#else 
    #define TITLE "Flight (Debug)"
    #define RENDER_X_RESOLUTION 1280
    #define RENDER_Y_RESOLUTION 720
    #define FULL_SCREEN false
#endif

struct GameConfig {
    const char *version = VERSION;
    const char *title = TITLE;
    int width = RENDER_X_RESOLUTION;
    int height = RENDER_Y_RESOLUTION;
    bool fullscreen = FULL_SCREEN;
};

#endif