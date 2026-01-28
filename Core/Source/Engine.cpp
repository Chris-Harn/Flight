#include "Engine.h"

//#include "OpenGL\Window.h"

#include "Logger.h"
#include "Timer.h"

Engine *Engine::s_pInstance = 0;

Engine::Engine() {
    m_bRunning = false;
    m_pMainWindow = nullptr;
    m_pTimer = nullptr;
}

bool Engine::Init() {
    TheLogger::Instance()->Printf_tstamp( "Flight Version : 0.0.1\n" );

    //TheLogger::Instance()->Printf_message( "Program started without issue.\n" );
    //try { m_pMainWindow = new Window(); }
    //catch( const std::bad_alloc &e ) {
    //    (void)e;
    //    TheLogger::Instance()->LogError( "ERROR: MEMORY ALLOCATION: Main Window failed to allocate on heap." );
    //    return false;
    //}
    //if( m_pMainWindow->Initialization( windowWidth, windowHeight, title, fullScreen ) != true ) {
    //    TheLogger::Instance()->LogError( "ERROR: EXIT EARLY: Main window failed to initalize." );
    //    return false;
    //}

    try { m_pTimer = new Timer(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheLogger::Instance()->LogError( "ERROR: MEMORY ALLOCATION: Timer failed to allocate on heap." );
        return false;
    }
    m_pTimer->Tick();

    // Everything started up without issue...
    m_bRunning = true;

    return true;
}

void Engine::HandleEvents() {
    m_pTimer->Tick();
}

void Engine::Render() {

}

void Engine::Clean() {
    if( m_pTimer != nullptr ) {
        delete m_pTimer;
        m_pTimer = nullptr;
    }

    TheLogger::Instance()->Printf_tstamp( "Program ended.\n" );
    TheLogger::Instance()->CloseFile();
}

bool Engine::Running() {
    static int count = 0;
    count++;

    if( count > 100000000 ) m_bRunning = false;

    return m_bRunning;
}
