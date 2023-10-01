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

    m_pTerran = nullptr;
    m_pTerran2 = nullptr;
    m_pTerran3 = nullptr;
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

    try { m_pCamera = new Camera( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ), -90.0f, 0.0f, 0.8f, 10.0f ); }
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

    //if( SetupTempAssets() == false ) return false;
    ResourceManager::LoadShader( "Resource/Shaders/DrawMesh.glsl", "DrawMesh" );

    // Create a pyramid so we have something temporary to look at
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
        2, 0, 3,
        0, 2, 1
    };
    GLfloat vertices[] = {
        -1.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  0.0f,
         0.0f,  1.0f,  0.5f
    };
    try { m_pTerran = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Terran1 failed to allocate on heap." );
        return false;
    }
    m_pTerran->CreateMesh( vertices, indices, 12, 12 );
    m_pTerran->m_model = glm::mat4( 1.0f );
    m_pTerran->m_model = glm::translate( m_pTerran->m_model, glm::vec3( 1.0f, 1.0f, -1.5f ) );
    m_pTerran->m_model = glm::scale( m_pTerran->m_model, glm::vec3( 0.8f, 1.0f, 1.0f ) );

    // Create a separate triangle for use in the tutorial
    unsigned int indices2[] = {
        // Front
        0, 1, 3,
        1, 2, 3,
        // Left
        5, 0, 4,
        5, 1, 0,
        // Right
        2, 7, 3,
        2, 6, 7,
        // Top
        0, 7, 4,
        0, 3, 7,
        // Bottom
        5, 2, 1,
        5, 6, 2,
        // Back
        6, 4, 7,
        6, 5, 4
    };
    float vertices2[] = {
        // Front Box
         0.5f,  0.5f,  0.0f, // 0
         0.5f, -0.5f,  0.0f, // 1
        -0.5f, -0.5f,  0.0f, // 2
        -0.5f,  0.5f,  0.0f, // 3
        // Back Box
         0.5f,  0.5f,  0.5f, // 4
         0.5f, -0.5f,  0.5f, // 5
        -0.5f, -0.5f,  0.5f, // 6
        -0.5f,  0.5f,  0.5f  // 7
    };
    try { m_pTerran2 = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Terran2 failed to allocate on heap." );
        return false;
    }
    m_pTerran2->CreateMesh( vertices2, indices2, 24, 36 );
    m_pTerran2->m_model = glm::mat4( 1.0f );
    m_pTerran2->m_model = glm::translate( m_pTerran->m_model, glm::vec3( 1.0f, 1.0f, -1.5f ) );
    m_pTerran2->m_model = glm::scale( m_pTerran->m_model, glm::vec3( 2.0f, 2.0f, 2.0f ) );

    unsigned int indices3[]{
        0, 1, 2,
        2, 1, 3
    };

    float vertices3[]{
        -1.0f,  0.0f, -1.0f,
        -1.0f,  0.0f,  1.0f,
         1.0f,  0.0f, -1.0f,
         1.0f,  0.0f,  1.0f
    };
    try { m_pTerran3 = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Terran3 failed to allocate on heap." );
        return false;
    }
    m_pTerran3->CreateMesh( vertices3, indices3, 12, 6 );
    m_pTerran3->m_model = glm::mat4( 1.0f );
    m_pTerran3->m_model = glm::translate( m_pTerran3->m_model, glm::vec3( 0.0f, -5.0f, 0.0f ) );
    m_pTerran3->m_model = glm::scale( m_pTerran3->m_model, glm::vec3( 1000.0f, 1000.0f, 1000.0f ) );

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

    //UpdateTempAssets();

    // Update Objects
    static float angle = 360.0f / 3.141565f;
    m_pTerran2->m_model = glm::mat4( 1.0f );
    m_pTerran2->m_model = glm::rotate( m_pTerran2->m_model, angle, glm::vec3( 0.1f, -0.5f, 1.0f ) );
    m_pTerran2->m_model = glm::scale( m_pTerran2->m_model, glm::vec3( 2.0f, 2.0f, 2.0f ) );
    angle += 0.01f / 3.141565f * m_pTimer->GetDeltaTime();
    if( angle >= 360.0f ) angle = 0.0f;
}

void Engine::Render() {
    m_pMainWindow->ClearColorBuffer();

    //RenderTempAssets();

    ResourceManager::GetShader( "DrawMesh" )->SetMat4( "projection", m_pCamera->m_projection, true );
    ResourceManager::GetShader( "DrawMesh" )->SetMat4( "view", m_pCamera->CalculateViewMatrix(), true );
    ResourceManager::GetShader( "DrawMesh" )->SetMat4( "model", m_pTerran->m_model, true );
    m_pTerran->RenderMesh();

    ResourceManager::GetShader( "DrawMesh" )->SetMat4( "model", m_pTerran2->m_model, true );
    m_pTerran2->RenderMesh();

    ResourceManager::GetShader( "DrawMesh" )->SetMat4( "model", m_pTerran3->m_model, true );
    m_pTerran3->RenderMesh();

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

    //CleanTempAssets();

    if( m_pTerran != nullptr ) {
        m_pTerran->Clean();
        delete m_pTerran;
        m_pTerran = nullptr;
    }
    if( m_pTerran2 != nullptr ) {
        m_pTerran2->Clean();
        delete m_pTerran2;
        m_pTerran2 = nullptr;
    }
    if( m_pTerran3 != nullptr ) {
        m_pTerran3->Clean();
        delete m_pTerran3;
        m_pTerran3 = nullptr;
    }
}

bool Engine::Running() {
    return m_bRunning;
}
    