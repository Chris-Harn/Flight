#include "Timer.h"

#include <iostream> // std::cout

Timer::Timer() {
    m_currentCountFPS = 0;
    m_FPS = 0;

    m_startTime = std::chrono::high_resolution_clock::now();
    m_currentTime = m_lastFrameTime = m_startTime;

    m_deltaTime = 0.0;
}

Timer::~Timer() {

}

void Timer::Tick() {
    m_currentCountFPS++;

    // Compute delta time in milliseconds
    m_currentTime = std::chrono::high_resolution_clock::now();
    m_deltaTime = std::chrono::duration<double, std::milli>( m_currentTime - m_lastFrameTime ).count();
    m_lastFrameTime = m_currentTime;

    // Calculate the FPS once per 1000ms
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>( m_currentTime - m_startTime );
    // Check if 1 second elapsed
    if( elapsedTime.count() >= 1000.0 ) {
        m_FPS = m_currentCountFPS;
        m_currentCountFPS = 0;
        m_startTime = m_currentTime;

        std::cout << "FPS = " << m_FPS << " which is " << 1000.0f / m_FPS << "ms.\n";
    }
}

double Timer::GetDeltaTime() {
    return m_deltaTime;
}

int Timer::GetFPSValue() {
    return m_FPS;
}