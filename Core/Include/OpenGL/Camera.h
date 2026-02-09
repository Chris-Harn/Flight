#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp> // glm::vec2, glm::vec3, glm::mat4

#include <GL/glew.h>

class Camera {
public:
    Camera();
    Camera( glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed );
    ~Camera();

    void KeyControl( bool *keys, GLfloat deltaTime );
    void MouseControl( GLfloat xChange, GLfloat yChange );

    glm::mat4 CalculateViewMatrix();
    glm::vec3 GetCameraPosition() { return m_position; }
    void UpdateCameraYPosition( float newYPosition );

    glm::mat4 m_projection; // Camera Projection

private:
    glm::vec3 m_position; // Camera position
    glm::vec3 m_front; // Camera front
    glm::vec3 m_up; // Camera up
    glm::vec3 m_right; // Camera right
    glm::vec3 m_worldUp; // Sky up

    GLfloat m_yaw;
    GLfloat m_pitch;

    GLfloat m_moveSpeed;
    GLfloat m_turnSpeed;

    glm::vec3 m_startPosition;
    GLfloat m_startYaw;
    GLfloat m_startPitch;

    void Update();
};

#endif