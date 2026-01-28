#ifndef __GAME__
#define __GAME__

#ifdef RELEASE    
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
    const char *title = TITLE;
    int width = RENDER_X_RESOLUTION;
    int height = RENDER_Y_RESOLUTION;
    bool fullscreen = FULL_SCREEN;
};

//class Game {
//public:
//
//private:
//
//};

#endif