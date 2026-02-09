#include "OpenGL/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include <math.h>

Camera::Camera() {
    m_position = glm::vec3( 0.0f );
    m_front = glm::vec3( 0.0f );
    m_up = glm::vec3( 0.0f );
    m_right = glm::vec3( 0.0f );
    m_worldUp = glm::vec3( 0.0f );

    m_projection = glm::mat4( 0.0f );

    m_yaw = 0.0f;
    m_pitch = 0.0f;

    m_moveSpeed = 0.0f;
    m_turnSpeed = 0.0f;

    m_startPosition = glm::vec3( 0.0f );
    m_startYaw = 0.0f;
    m_startPitch = 0.0f;
}

Camera::Camera( glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed ) {
    m_position = m_startPosition = startPosition;
    m_worldUp = startUp;
    m_yaw = m_startYaw = startYaw;
    m_pitch = m_startPitch = startPitch;
    m_front = glm::vec3( 0.0f, 0.0f, -1.0f );

    m_moveSpeed = startMoveSpeed;
    m_turnSpeed = startTurnSpeed;

    Update();
}

Camera::~Camera() {
    // Never clear OpenGL resources in deconstructor
}

void Camera::KeyControl( bool *keys, GLfloat deltaTime ) {
    GLfloat velocity = m_moveSpeed * deltaTime * 0.01f;

    // Keyboard Controls
    if( keys[GLFW_KEY_W] ) m_position += m_front * velocity;
    if( keys[GLFW_KEY_S] ) m_position -= m_front * velocity;
    if( keys[GLFW_KEY_A] ) m_position -= m_right * velocity;
    if( keys[GLFW_KEY_D] ) m_position += m_right * velocity;
    if( keys[GLFW_KEY_Q] ) m_yaw -= m_turnSpeed * velocity;
    if( keys[GLFW_KEY_E] ) m_yaw += m_turnSpeed * velocity;
    if( keys[GLFW_KEY_R] ) m_pitch += m_turnSpeed * velocity;
    if( keys[GLFW_KEY_F] ) m_pitch -= m_turnSpeed * velocity;
    if( keys[GLFW_KEY_Z] ) m_position += m_worldUp * velocity;
    if( keys[GLFW_KEY_X] ) m_position -= m_worldUp * velocity;
    if( keys[GLFW_KEY_C] ) m_pitch = m_startPitch * velocity;

    // Reset Position
    if( keys[GLFW_KEY_P] ) {
        m_position = m_startPosition;
        m_yaw = m_startYaw;
        m_pitch = m_startPitch;
    }
}

void Camera::MouseControl( GLfloat xChange, GLfloat yChange ) {
    static int count = 0;

    // Mouse Acceleration addition
    if( xChange != 0.0f || yChange != 0.0f ) {
        count++;

        xChange *= m_turnSpeed * 0.7f * float( 1.0f - exp( -1 * count ) );
        yChange *= m_turnSpeed * 0.3f * float( 1.0f - exp( -1 * count ) );

        m_yaw += xChange;
        m_pitch += yChange;

        if( m_pitch > 89.0f ) m_pitch = 89.0f;
        if( m_pitch < -89.0f ) m_pitch = -89.0f;

        Update();
    }
    else {
        count = 0;
    }
}

glm::mat4 Camera::CalculateViewMatrix() {
    return glm::lookAt( m_position, m_position + m_front, m_up );
}

void Camera::Update() {
    m_front.x = cos( glm::radians( m_yaw ) ) * cos( glm::radians( m_pitch ) );
    m_front.y = sin( glm::radians( m_pitch ) );
    m_front.z = sin( glm::radians( m_yaw ) ) * cos( glm::radians( m_pitch ) );
    m_front = glm::normalize( m_front ); // removes magnitude
    m_right = glm::normalize( glm::cross( m_front, m_worldUp ) );
    m_up = glm::normalize( glm::cross( m_right, m_front ) );
}

void Camera::UpdateCameraYPosition( float newYPosition ) { 
    m_position.y = newYPosition; 
}