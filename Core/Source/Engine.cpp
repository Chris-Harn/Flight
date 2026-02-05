#include "Engine.h"

// OpenGL Utilities
#include "OpenGL\Window.h"

// Utilities
#include "ModernLogger.h"
#include "Timer.h"

// Game Specific Files
#include "Game.h"

Engine *Engine::s_pInstance = 0;

Engine::Engine() {
    m_bRunning = false;
    m_pMainWindow = nullptr;
    m_pTimer = nullptr;
}

bool Engine::Init() {
    GameConfig config;

    TheMLogger::Instance()->Open( ".\\logs" );
    TheMLogger::Instance()->Info( "Flight Version : {}", config.version );

    try { m_pMainWindow = new Window(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheMLogger::Instance()->Error( "ERROR: MEMORY ALLOCATION: Main Window failed to allocate on heap." );
        return false;
    }
    if( m_pMainWindow->Initialization( config ) != true ) {
        TheMLogger::Instance()->Error( "ERROR: EXIT EARLY: Main window failed to initalize." );
        return false;
    }

    try { m_pTimer = new Timer( 60, true ); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheMLogger::Instance()->Error( "ERROR: MEMORY ALLOCATION: Timer failed to allocate on heap." );
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

    TheMLogger::Instance()->Info( "Program ended." );
    TheMLogger::Instance()->CloseFile();
}

bool Engine::Running() {
    return m_bRunning;
}
