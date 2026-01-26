#ifndef __MAIN__
#define __MAIN__

#ifdef RELEASE    
#define TITLE "Flight"
#define UPSCALED_X_RESOLUTION 1920
#define UPSCALED_Y_RESOLUTION 1080
#define RENDER_X_RESOLUTION 1280
#define RENDER_Y_RESOLUTION 720
#define FULL_SCREEN true
#else 
#define TITLE "Flight (Debug)"
#define UPSCALED_X_RESOLUTION 1920
#define UPSCALED_Y_RESOLUTION 1080
#define RENDER_X_RESOLUTION 1280
#define RENDER_Y_RESOLUTION 720
#define FULL_SCREEN false
#endif


#endif