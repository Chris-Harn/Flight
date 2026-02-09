#include "CollisionDetection.h"

#include "OpenGL/Camera.h"

void Collision::CameraCollidingWithGround( Camera *gameCamera ) {
    // Prevent clipping through ground
    if( gameCamera->GetCameraPosition().y < -0.2f ) gameCamera->UpdateCameraYPosition( -0.2f );
}