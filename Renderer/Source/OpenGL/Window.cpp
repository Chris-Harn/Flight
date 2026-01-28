#include "OpenGL\Window.h"
#include "Logger.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#ifdef _DEBUG
#include <stdio.h>
#endif

Window::Window() {
    m_pWindow = nullptr;
    m_BufferWidth = 0;
    m_BufferHeight = 0;
    m_lastX = 0.0f;
    m_lastY = 0.0f;
    m_xChange = 0.0f;
    m_yChange = 0.0f;
    m_bMouseFirstMove = true;
    m_vSync = false;

    // Clear all the keys
    for( int i = 0; i < TOTAL_KEYS; i++ ) {
        m_bKeys[i] = false;
    }
}

Window::~Window() {

}

bool Window::Initialization( unsigned int width,
    unsigned int height,
    const char *title,
    bool fullscreen ) {
    /**************************************************************************/
    /*** Setup Main Window                                                  ***/
    /***                                                                    ***/
    /**************************************************************************/
    if( glfwInit() == false ) {
        TheLogger::Instance()->LogError( "ERROR: EXIT EARLY: GLFW Initialization failed." );
        glfwTerminate();
        return false;
    }

    // Setup GLFW window properties with OpenGL version
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
    // Core profile = No backwards compatibility and best performance
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    // Allow forward compatiblity
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

    // Lock current aspect ratio - Must be before window creation
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

    GLFWmonitor *monitor;
    if( fullscreen == true ) {
        monitor = glfwGetPrimaryMonitor();
    }
    else {
        monitor = nullptr;
    }

    m_pWindow = glfwCreateWindow( width, height, title, monitor, nullptr );
    if( !m_pWindow ) {
        TheLogger::Instance()->LogError( "ERROR: EXIT EARLY: GLFW main window creation failed." );
        glfwTerminate();
        return false;
    }

    // Get context for GLEW to use
    glfwMakeContextCurrent( m_pWindow );

    // Get buffer size information
    glfwGetFramebufferSize( m_pWindow, &m_BufferWidth, &m_BufferHeight );

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if( glewInit() != GLEW_OK ) {
        TheLogger::Instance()->LogError( "ERROR: EXIT EARLY: GLEW main window initialization failed." );
        glfwDestroyWindow( m_pWindow );
        glfwTerminate();
        return false;
    }

    // Setup Viewport Size
    glViewport( 0, 0, m_BufferWidth, m_BufferHeight );

    // Tell window to stay open
    glfwSetWindowShouldClose( m_pWindow, GL_FALSE );

    // Disable VSYNC as framerate timer handles it
    glfwSwapInterval( m_vSync );

    // Handle Keys
    CreateCallbacks();

    // Enable mouse control
    glfwSetInputMode( m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    glfwSetWindowUserPointer( m_pWindow, this );

    // Setup camera for depth buffering
    glEnable( GL_DEPTH_TEST );
    glDepthMask( GL_TRUE );
    glDepthFunc( GL_LEQUAL );
    glDepthRange( 0.0f, 1.0f );

    return true;
}


void Window::CreateCallbacks() {
    // Setup GLFW callback that uses this object as owner
    // or else keys won't work
    glfwSetWindowUserPointer( m_pWindow, this );

    glfwSetKeyCallback( m_pWindow, HandleKeys );
    glfwSetInputMode( m_pWindow, GLFW_STICKY_KEYS, 1 );

    glfwSetCursorPosCallback( m_pWindow, HandleMouse );
}

void Window::ClearColorBuffer() {
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClearDepth( 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Window::SwapBuffers() {
    glfwSwapBuffers( m_pWindow );
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::Clean() {
    if( m_pWindow != nullptr ) {
        glfwDestroyWindow( m_pWindow );
        m_pWindow = nullptr;
    }

    glfwTerminate();
}

bool *Window::GetsKeys() {
    return m_bKeys;
}

GLFWwindow *Window::GetWindow() {
    return m_pWindow;
}

bool Window::GetShouldClose() {
    return glfwWindowShouldClose( m_pWindow );
}

void Window::HandleKeys( GLFWwindow *window, int key, int code, int action, int mode ) {
    // Window pointer user function
    Window *theWindow = static_cast<Window *>( glfwGetWindowUserPointer( window ) );

    if( ( key == GLFW_KEY_ESCAPE ) && ( action == GLFW_PRESS ) ) {
        glfwSetWindowShouldClose( window, GL_TRUE );
        theWindow->m_bKeys[key] = true;
    }

    // Trouble Shooting Code
    if( ( key >= 0 ) && ( key < 1024 ) ) {
        if( action == GLFW_PRESS ) {
            theWindow->m_bKeys[key] = true;
            #ifdef _DEBUG
                TheLogger::Instance()->Printf_message( "Pressed: %d\n", key );
            #endif
        }
        else if( action == GLFW_RELEASE ) {
            theWindow->m_bKeys[key] = false;
            #ifdef _DEBUG
                TheLogger::Instance()->Printf_message( "Pressed: %d\n", key );
            #endif
        }
    }
}

void Window::HandleMouse( GLFWwindow *window, double xPos, double yPos ) {
    Window *theWindow = static_cast<Window *>( glfwGetWindowUserPointer( window ) );

    if( theWindow->m_bMouseFirstMove ) {
        theWindow->m_lastX = xPos;
        theWindow->m_lastY = yPos;
        theWindow->m_bMouseFirstMove = false;
    }

    theWindow->m_xChange = xPos - theWindow->m_lastX;
    theWindow->m_yChange = theWindow->m_lastY - yPos;

    theWindow->m_lastX = xPos;
    theWindow->m_lastY = yPos;
}

bool Window::IsKeyUp( int key ) {
    if( key != 0 ) {
        return !m_bKeys[key];
    }

    return false;
}

bool Window::IsKeyDown( int key ) {
    if( key != 0 ) {
        return m_bKeys[key];
    }

    return false;
}

float Window::GetBufferWidth() {
    return (float)m_BufferWidth;
}

float Window::GetBufferHeight() {
    return (float)m_BufferHeight;
}

GLfloat Window::GetXChange() {
    GLfloat theChange = m_xChange;
    m_xChange = 0.0f;
    return theChange;
}

GLfloat Window::GetYChange() {
    GLfloat theChange = m_yChange;
    m_yChange = 0.0f;
    return theChange;
}

void Window::ToggleVsync( bool vsync ) {
    m_vSync = vsync;
    glfwSwapInterval( m_vSync );
}

void Window::ToggleWireFrame( bool setWireFrame ) {
    if( setWireFrame == true ) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
    else {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
}

bool Window::GetVsync() {
    return m_vSync;
}