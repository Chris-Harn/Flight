#include "OpenGL/Window.h"

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>

Window::Window() {
    m_pMainWindow = nullptr;
    m_bufferWidth = 0;
    m_bufferHeight = 0;

    // Clear all the keys
    for( int i = 0; i < TOTAL_KEYS; i++ ) {
        m_bKeys[i] = false;
    }
}

Window::~Window() {

}

bool Window::Initialize( unsigned int width,
    unsigned int height,
    const char *title,
    bool fullScreen ) {

    //if( glfwInit() == false ) {
    //    print_error_message( "ERROR: EXIT EARLY: GLFW Initialization failed." );
    //    glfwTerminate();
    //    return false;
    //}

    //// Setup GLFW window properties with OpenGL version
    //glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    //glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
    //glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    //glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

    //// Lock current aspect ratio - Must be before window creation
    //glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

    //GLFWmonitor *monitor;
    //if( fullScreen == true ) {
    //    monitor = glfwGetPrimaryMonitor();
    //}
    //else {
    //    monitor = nullptr;
    //}

    //m_pMainWindow = glfwCreateWindow( width, height, title, monitor, nullptr );
    //if( !m_pMainWindow ) {
    //    print_error_message( "ERROR: EXIT EARLY: GLFW main window creation failed." );
    //    glfwTerminate();
    //    return false;
    //}

    //// Get context for GLEW to use
    //glfwMakeContextCurrent( m_pMainWindow );

    //// Get buffer size information
    //glfwGetFramebufferSize( m_pMainWindow, &m_bufferWidth, &m_bufferHeight );

    //// Allow modern extension features
    //glewExperimental = GL_TRUE;

    //if( glewInit() != GLEW_OK ) {
    //    print_error_message( "ERROR: EXIT EARLY: GLEW main window initialization failed." );
    //    glfwDestroyWindow( m_pMainWindow );
    //    glfwTerminate();
    //    return false;
    //}

    //// Setup Viewport Size
    //glViewport( 0, 0, m_bufferWidth, m_bufferHeight );

    //// Tell window to stay open
    //glfwSetWindowShouldClose( m_pMainWindow, GL_FALSE );

    //// Disable VSYNC as framerate timer handles it
    //glfwSwapInterval( false );

    //// Handle Keys
    //CreateCallbacks();

    //// Setup camera for depth buffering
    //glEnable( GL_DEPTH_TEST );
    //glDepthMask( GL_TRUE );
    //glDepthFunc( GL_LEQUAL );
    //glDepthRange( 0.0f, 1.0f );

    return true;
}

void Window::PollEvents() {
    //glfwPollEvents();
}

void Window::ClearColorBuffer() {
    //glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
    //glClearDepth( 1.0f );
    //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Window::UpscaleImage() {

}

void Window::SwapBuffer() {
    //glfwSwapBuffers( m_pMainWindow );
}

bool Window::GetShouldClose() {
    return true;
    //return glfwWindowShouldClose( m_pMainWindow );
}

void Window::CreateCallbacks() {
    //// Setup GLFW callback that uses this object as owner
    //// or else keys won't work
    //glfwSetWindowUserPointer( m_pMainWindow, this );

    //glfwSetKeyCallback( m_pMainWindow, HandleKeys );
    //glfwSetInputMode( m_pMainWindow, GLFW_STICKY_KEYS, 1 );
}

void Window::HandleKeys( GLFWwindow *window,
    int key,
    int code,
    int action,
    int mode ) {
    //// Window pointer user function
    //Window *theWindow = static_cast<Window *>( glfwGetWindowUserPointer( window ) );

    //if( ( key == GLFW_KEY_ESCAPE ) && ( action == GLFW_PRESS ) ) {
    //    glfwSetWindowShouldClose( window, GL_TRUE );
    //    theWindow->m_bKeys[key] = true;
    //}

    //if( ( key >= 0 ) && ( key < TOTAL_KEYS ) ) {
    //    if( action == GLFW_PRESS ) {
    //        theWindow->m_bKeys[key] = true;
    //    }
    //    else if( action == GLFW_RELEASE ) {
    //        theWindow->m_bKeys[key] = false;
    //    }
    //}
}

void Window::Clean() {
    //if( m_pMainWindow != nullptr ) {
    //    glfwDestroyWindow( m_pMainWindow );
    //    m_pMainWindow = nullptr;
    //}

    //glfwTerminate();
}

bool *Window::GetsKeys() {
    return m_bKeys;
}

GLFWwindow *Window::GetWindow() {
    return m_pMainWindow;
}