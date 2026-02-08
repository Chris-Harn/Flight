#include "Engine.h"

// OpenGL Utilities
#include "OpenGL/ResourceManager.h"
#include "OpenGL/Helper.h"

// Utilities
#include "ModernLogger.h"

// Future remove
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Game Specific Files
#include "Game.h"
#include "SceneGraph.h"

Engine *Engine::s_pInstance = 0;

Engine::Engine() {
    m_bRunning = false;
    m_pMainWindow = nullptr;
    m_pCamera = nullptr;
    m_pTextRenderer = nullptr;
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
    if( m_pMainWindow->Initialization( &config ) != true ) {
        TheMLogger::Instance()->Error( "ERROR: EXIT EARLY: Main window failed to initalize." );
        return false;
    }

    try { m_pCamera = new Camera( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ), -90.0f, 0.0f, 0.8f, 2.0 ); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheMLogger::Instance()->Error( "ERROR: MEMORY ALLOCATION: Camera failed to allocate on heap." );
        return false;
    }
    m_pCamera->m_projection = glm::perspective( 45.0f, m_pMainWindow->GetBufferWidth() / m_pMainWindow->GetBufferHeight(), 0.1f, 100.0f );

    // Load Shaders, framebuffers, and other resources... 
    ResourceManager::LoadShader( "Resource/Shaders/CautionStrips.glsl", "CautionImage" ); // 0. Shader compile error

    ResourceManager::LoadShader( "Resource/Shaders/BlitImageToScreen.glsl", "BlitScreen" );
    ResourceManager::GetShader( "BlitScreen" )->SetInteger( "u_Texture", 0, true );

    ResourceManager::LoadShader( "Resource/Shaders/FastBlitTextToScreen.glsl", "FastBlitText" );
    ResourceManager::GetShader( "FastBlitText" )->SetInteger( "text", 0, true );

    try { m_pTextRenderer = new TextRenderer(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheMLogger::Instance()->Error( "ERROR: MEMORY ALLOCATION: Text Rendererer failed to allocate on heap." );
        return false;
    }
    m_pTextRenderer->Initialize( m_pMainWindow );

    try { m_pTimer = new Timer( 60, false ); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheMLogger::Instance()->Error( "ERROR: MEMORY ALLOCATION: Timer failed to allocate on heap." );
        return false;
    }
    m_pTimer->StartFrame();

    if( SetupTempAssets() == false ) return false;

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

    m_pCamera->KeyControl( m_pMainWindow->GetsKeys(), m_pTimer->GetDeltaTime() );
    m_pCamera->MouseControl( m_pMainWindow->GetXChange(), m_pMainWindow->GetYChange() );

    UpdateTempAssets();
}

void Engine::Render() {
    m_pMainWindow->ClearColorBuffer();

    RenderTempAssets();

    DisplayPerformanceInformation();

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
    if( m_pTextRenderer != nullptr ) {
        m_pTextRenderer->Clean();
        delete m_pTextRenderer;
        m_pTextRenderer = nullptr;
    }
    if( m_pCamera != nullptr ) {
        delete m_pCamera;
        m_pCamera = nullptr;
    }

    ResourceManager::Clean();

    TheMLogger::Instance()->Info( "Program ended." );
    TheMLogger::Instance()->CloseFile();

    CleanTempAssets();
}

bool Engine::Running() {
    return m_bRunning;
}
