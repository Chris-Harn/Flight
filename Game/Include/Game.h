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
    const int width = RENDER_X_RESOLUTION;
    const int height = RENDER_Y_RESOLUTION;
    const bool fullscreen = FULL_SCREEN;
};

struct CameraCOnfig {
    const double fieldOfView = 90.0;
    const double aspectRatio = double( RENDER_X_RESOLUTION ) / double( RENDER_Y_RESOLUTION );
    const double nearClip = 0.1;
    const double farClip = 500.0;
};
#endif