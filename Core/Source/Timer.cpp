#include "Timer.h"

#include "ModernLogger.h"

#include <thread>

void precisionSleepUntil( std::chrono::high_resolution_clock::time_point target );

Timer::Timer( int targetThisFPS, bool regulateThisFPS ) {
    // Variables for calculating FPS
    m_bRegulateTheFPS = regulateThisFPS;
    m_currentCountFPS = 0;
    m_lastFPS = 0;
    m_startTime = std::chrono::high_resolution_clock::now();
    m_currentTime = m_startTime;

    // Variables for regulating the fps
    m_nextFrameTime = m_startTime;
    m_frameTime = std::chrono::duration<double>( 1.0 / targetThisFPS );

    // Variables for calculating delta time
    m_lastDeltaTime = m_startTime;
    m_currentDeltaTime = m_startTime;
}

Timer::~Timer() {

}

void Timer::StartFrame() {
    m_currentCountFPS++;

    m_currentTime = std::chrono::high_resolution_clock::now();

    if( m_bRegulateTheFPS == true ) {
        // Compute next frame time without drift
        m_nextFrameTime = m_startTime + m_currentCountFPS * std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>( m_frameTime );
        std::this_thread::sleep_until( m_nextFrameTime );
        m_currentTime = std::chrono::high_resolution_clock::now();

        // Alternative sleep. Uses more clock cycles.
        //precisionSleepUntil( m_nextFrameTime );
    }

    // Calculate the fps once per second
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>( m_currentTime - m_startTime );

    // Check if one second elapsed
    if( elapsedTime.count() >= 1000.0 ) {
        m_lastFPS = m_currentCountFPS;
        m_currentCountFPS = 0;
        m_startTime = m_currentTime;
        TheMLogger::Instance()->Info( "FPS = {} which is {}ms.", m_lastFPS, 1000.0 / m_lastFPS );

        // Uncomment to see how accurate the delta time is... should be extremely close to 1000 ms. 
        //TheMLogger::Instance()->Info( "Delta Time : {}ms", GetDeltaTime() );
    }
}

double Timer::GetDeltaTime() {
    m_currentDeltaTime = std::chrono::high_resolution_clock::now();

    double deltaCount = std::chrono::duration<double, std::milli>( m_currentDeltaTime - m_lastDeltaTime ).count();
    m_lastDeltaTime = m_currentDeltaTime;

    return deltaCount;
}

int Timer::GetFPSValue() {
    return m_lastFPS;
}

void precisionSleepUntil( std::chrono::high_resolution_clock::time_point target ) {
    while( true ) {
        auto now = std::chrono::high_resolution_clock::now();
        auto remaining = target - now;

        if( remaining <= std::chrono::microseconds( 200 ) ) {
            // Busy wait for the last tiny bit
            while( std::chrono::high_resolution_clock::now() < target ) {}
            return;
        }

        // Sleep most of the remaining time
        std::this_thread::sleep_for( remaining - std::chrono::microseconds( 200 ) );
    }
}