#include "Engine.h"
#include "Logger.h"

Engine *Engine::s_pInstance = 0;

Engine::Engine() {
    m_bRunning = false;
}

bool Engine::Init() {
    TheLogger::Instance()->Open( "LatestLog.txt" );
    TheLogger::Instance()->Printf_ntstamp( "Flight Version : 0.0.1\n" );

    // Everything started up without issue...
    m_bRunning = true;

    return true;
}

void Engine::HandleEvents() {

}

void Engine::Render() {

}

void Engine::Clean() {
    TheLogger::Instance()->Printf_ntstamp( "Program ran cleanup.\n" );
}

bool Engine::Running() {
    static int count = 0;
    count++;

    if( count > 100000000 ) m_bRunning = false;

    return m_bRunning;
}
