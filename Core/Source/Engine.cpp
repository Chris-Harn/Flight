#include "Engine.h"

#include "OpenGL\Window.h"

#include "Logger.h"
#include "Timer.h"

#include "Game.h"

Engine *Engine::s_pInstance = 0;

Engine::Engine() {
    m_bRunning = false;
    m_pMainWindow = nullptr;
    m_pTimer = nullptr;
}

bool Engine::Init() {
    TheLogger::Instance()->Printf_tstamp( "Flight Version : 0.0.1\n" );

    GameConfig config;

    try { m_pMainWindow = new Window(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheLogger::Instance()->LogError( "ERROR: MEMORY ALLOCATION: Main Window failed to allocate on heap." );
        return false;
    }
    if( m_pMainWindow->Initialization( config ) != true ) {
        TheLogger::Instance()->LogError( "ERROR: EXIT EARLY: Main window failed to initalize." );
        return false;
    }

    try { m_pTimer = new Timer( 60, true ); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheLogger::Instance()->LogError( "ERROR: MEMORY ALLOCATION: Timer failed to allocate on heap." );
        return false;
    }
    m_pTimer->StartFrame();

    // Everything started up without issue...
    m_bRunning = true;

    return true;
}

void Engine::HandleEvents() {
    m_pTimer->StartFrame();
    m_pMainWindow->PollEvents();

    // Close Window Commands
    if( ( m_pMainWindow->GetsKeys()[256] == true ) ||
        ( m_pMainWindow->GetShouldClose() == true ) ) {
        m_bRunning = false; // GLFW_KEY_ESCAPE
    }
}

void Engine::Render() {
    m_pMainWindow->ClearColorBuffer();

    m_pMainWindow->SwapBuffers();
}

void Engine::Clean() {
    if( m_pMainWindow != nullptr ) {
        m_pMainWindow->Clean();
        delete m_pMainWindow;
        m_pMainWindow = nullptr;
    }

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
