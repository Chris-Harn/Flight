#include "Engine.h"

#include "OpenGL/Window.h"
#include "OpenGL/TextRenderer.h"
#include "OpenGL/Camera.h"
#include "OpenGL/Quad.h"
#include "OpenGL/Mesh.h"
#include "OpenGL/Shader.h"
#include "OpenGL/ResourceManager.h"
#include "OpenGL/Helper.h"
#include "Logger.h"
#include "Timer.h"

#include <iostream> // std::bad_alloc
#include <chrono>   // std::chrono::milliseconds
#include <thread>   // std::this_thread::sleep_for

#include <string>   // std::to_string

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Temp
#include "OpenGL/Temp.h"

Engine *Engine::s_pInstance = 0;

Engine::Engine() {
    m_bRunning = true;
    m_bDisplayText = true;
    m_pMainWindow = nullptr;
    m_pTimer = nullptr;
    m_pTextRenderer = nullptr;

    m_pCamera = nullptr;
    m_pQuad = nullptr;
}

bool Engine::Init( const char *title, int windowWidth, int windowHeight, bool fullScreen ) {
    print_message( "Program started without issue.\n" );
    try { m_pMainWindow = new Window(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Main Window failed to allocate on heap." );
        return false;
    }
    if( m_pMainWindow->Initialization( windowWidth, windowHeight, title, fullScreen ) != true ) {
        print_error_message( "ERROR: EXIT EARLY: Main window failed to initalize." );
        return false;
    }

    try { m_pCamera = new Camera( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ), -90.0f, 0.0f, 0.8f, 2.0 ); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Camera failed to allocate on heap." );
        return false;
    }
    m_pCamera->m_projection = glm::perspective( 45.0f, m_pMainWindow->GetBufferWidth() / m_pMainWindow->GetBufferHeight(), 0.1f, 100.0f );

    try { m_pQuad = new Quad(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Quad failed to allocate on heap." );
        return false;
    }

    // Load Shaders, framebuffers, and other resources... 
    ResourceManager::LoadShader( "Resource/Shaders/CautionStrips.glsl", "CautionImage" ); // 0. Shader compile error
    
    ResourceManager::LoadShader( "Resource/Shaders/BlitImageToScreen.glsl", "BlitScreen" );
    ResourceManager::GetShader( "BlitScreen" )->SetInteger( "u_Texture", 0, true );

    ResourceManager::LoadShader( "Resource/Shaders/FastBlitTextToScreen.glsl", "FastBlitText" );
    ResourceManager::GetShader( "FastBlitText" )->SetInteger( "text", 0, true );

    try { m_pTextRenderer = new TextRenderer(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Text Rendererer failed to allocate on heap." );
        return false;
    }
    m_pTextRenderer->Initialize( m_pMainWindow );

    try { m_pTimer = new Timer( 60 ); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Timer failed to allocate on heap." );
        return false;
    }
    m_pTimer->Tick();

    // Allocate and initalize temp assets that will change
    // as the engine progresses and matures
    if( SetupTempAssets() == false ) return false;

    return true;
}

void Engine::HandleEvents() {
    m_pTimer->Tick();
    m_pMainWindow->PollEvents();

    // Close Window Commands
    if( ( m_pMainWindow->GetsKeys()[256] == true ) ||
        ( m_pMainWindow->GetShouldClose() == true ) ) {
            m_bRunning = false; // GLFW_KEY_ESCAPE
    }

    // Display Performance Text
    if ( m_pMainWindow->GetsKeys()[49] == true ) {
        m_bDisplayText = true;  // GLFW KEY 1
    }

    // Remove Performance Text
    if( m_pMainWindow->GetsKeys()[50] == true ) {
        m_bDisplayText = false; // GLFW KEY 2
    }

    // Toggle VSYNC on
    if( m_pMainWindow->GetsKeys()[GLFW_KEY_N] == true ) {
        m_pMainWindow->ToggleVsync( true );
    }

    // Toggle VSYNC off
    if( m_pMainWindow->GetsKeys()[GLFW_KEY_M] == true ) {
        m_pMainWindow->ToggleVsync( false );
    }

    // Toggle FPS regulator on
    if( m_pMainWindow->GetsKeys()[GLFW_KEY_V] == true ) {
        m_pTimer->RegulateFPS( true );
    }

    // Toggle FPS regulator off
    if( m_pMainWindow->GetsKeys()[GLFW_KEY_B] == true ) {
        m_pTimer->RegulateFPS( false );
    }

    // Toggle Wireframe Mode on
    if( m_pMainWindow->GetsKeys()[GLFW_KEY_COMMA] == true ) {
        m_pMainWindow->ToggleWireFrame( true );
    }

    // Toggle Wireframe Mode off
    if( m_pMainWindow->GetsKeys()[GLFW_KEY_PERIOD] == true ) {
        m_pMainWindow->ToggleWireFrame( false );
    }

    m_pCamera->KeyControl( m_pMainWindow->GetsKeys(), m_pTimer->GetDeltaTime() );
    m_pCamera->MouseControl( m_pMainWindow->GetXChange(), m_pMainWindow->GetYChange() );

    UpdateTempAssets();
}

void Engine::Render() {
    m_pMainWindow->ClearColorBuffer();

    RenderTempAssets();

    if(m_bDisplayText == true ) {
        DisplayPerformanceInformation();
    }

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
    if( m_pQuad != nullptr ) {
        m_pQuad->Clean();
        delete m_pQuad;
        m_pQuad = nullptr;
    }
    ResourceManager::Clean();

    CleanTempAssets();
}

bool Engine::Running() {
    return m_bRunning;
}
    