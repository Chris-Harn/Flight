#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>

class Timer {
public:
    Timer();
    ~Timer();
    void Tick();
    double GetDeltaTime();
    int GetFPSValue();

private:
    unsigned int m_currentCountFPS;
    unsigned int m_FPS;

    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastFrameTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_currentTime;
    double m_deltaTime; // milliseconds between frames
};

#endif