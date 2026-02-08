#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>

class Timer {
public:
    Timer( int targetThisFPS, bool regulateThisFPS );
    ~Timer();

    void StartFrame();
    double GetDeltaTime();
    int GetFPSValue();
    bool GetRegulationValue();
    void RegulateFPS( bool regulateThisFPS ); 

    // Prevent copying
    Timer( const Timer& ) = delete;
    Timer &operator=( const Timer& ) = delete;
private:
    // Variables for regulating the framerate
    int m_targetThisFPS;
    bool m_bRegulateFPS;
    std::chrono::milliseconds m_frameDuration;
    std::chrono::high_resolution_clock::time_point m_lastFrameTime; // milliseconds between frames

    // Variables for calculating delta time
    double m_deltaTime;

    // Variables for calculating frame rate variables
    int m_frames;
    int m_fps;
    std::chrono::high_resolution_clock::time_point m_lastSecondTime;// milliseconds between frames
};

#endif