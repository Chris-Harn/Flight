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

    // Prevent copying
    Timer( const Timer& ) = delete;
    Timer &operator=( const Timer& ) = delete;
private:
    // Variables for regulating the framerate
    bool m_bRegulateTheFPS;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_nextFrameTime;
    std::chrono::duration<double> m_frameTime; // milliseconds between frames

    // Variables for calculating delta time
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastDeltaTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_currentDeltaTime;

    // Variables for calculating frame rate variables
    unsigned int m_currentCountFPS;
    unsigned int m_lastFPS;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastFrameTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_currentTime;
};

#endif