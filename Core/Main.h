#ifndef __MAIN__
#define __MAIN__

#ifdef RELEASE    
    #define TITLE "Flight"
    #define X_RESOLUTION 1920
    #define Y_RESOLUTION 1080
    #define FULL_SCREEN true
#else 
    #define TITLE "Flight (Debug)"
    #define X_RESOLUTION 800
    #define Y_RESOLUTION 600
    #define FULL_SCREEN false
#endif


#endif