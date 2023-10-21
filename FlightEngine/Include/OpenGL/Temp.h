#ifndef __TEMP__
#define __TEMP__

#include "Engine.h"
#include "OpenGL/Mesh.h"
#include "OpenGL/ResourceManager.h"
#include "Logger.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* These are temporary functions and assets that will eventually be removed.*/
/* Same with the assets being global. */
Mesh *m_pPyramid;
Mesh *m_pTerrain;
Mesh *m_pSquare;
Mesh *m_pLight;

bool SetupTempAssets();
void UpdateTempAssets();
void RenderTempAssets();

bool SetupTempAssets() {
    m_pPyramid = nullptr;
    m_pTerrain = nullptr;
    m_pSquare = nullptr;
    m_pLight = nullptr;

    ResourceManager::LoadShader( "Resource/Shaders/Light.glsl", "Light" ); // Light
    ResourceManager::LoadShader( "Resource/Shaders/SimpleLight.glsl", "SimpleLight" ); // Diffuse + Ambient

    // Create a pyramid so we have normals to check against.
    GLfloat vertices[] = {
        // vec3 Bottom Left Square, vec3 normals
        -1.0f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f,
         0.0f,  0.0f, -1.0f,  0.0f, -1.0f,  0.0f,
         0.0f,  0.0f,  1.0f,  0.0f, -1.0f,  0.0f,
        // Bottom Right Square
         0.0f,  0.0f, -1.0f,  0.0f, -1.0f,  0.0f,
         1.0f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f,
         0.0f,  0.0f,  1.0f,  0.0f, -1.0f,  0.0f,
        // Slope 1
         0.0f,  1.0f,  0.0f,  -0.57f, 0.57f, 0.57f,
        -1.0f,  0.0f,  0.0f,  -0.57f, 0.57f, 0.57f,
         0.0f,  0.0f,  1.0f,  -0.55f, 0.57f, 0.57f,
        // Slope 2
         0.0f,  1.0f,  0.0f,  -0.57f, 0.57f, -0.57f,
         0.0f,  0.0f, -1.0f,  -0.57f, 0.57f, -0.57f,
        -1.0f,  0.0f,  0.0f,  -0.57f, 0.57f, -0.57f,
        // Slope 3
         0.0f,  1.0f,  0.0f,  0.57f, 0.57f, -0.57f,
         1.0f,  0.0f,  0.0f,  0.57f, 0.57f, -0.57f,
         0.0f,  0.0f, -1.0f,  0.57f, 0.57f, -0.57f,
        // Slope 4
         0.0f,  1.0f,  0.0f,  0.57f, 0.57f, 0.57f,
         0.0f,  0.0f,  1.0f,  0.57f, 0.57f, 0.57f,
         1.0f,  0.0f,  0.0f,  0.57f, 0.57f, 0.57f,
    };

    try { m_pPyramid = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Pyramid failed to allocate on heap." );
        return false;
    }
    m_pPyramid->CreateMesh( vertices, 108 );
    m_pPyramid->m_model = glm::mat4( 1.0f );
    m_pPyramid->m_model = glm::translate( m_pPyramid->m_model, glm::vec3( 1.0f, 1.0f, -1.5f ) );

    float vertices2[] = {
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f
    };
    try { m_pSquare = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Square failed to allocate on heap." );
        return false;
    }
    m_pSquare->CreateMesh( vertices2, 216 );

    try { m_pLight = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Light failed to allocate on heap." );
        return false;
    }
    m_pLight->CreateMesh( vertices2, 216 );

    float vertices3[]{
        -1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
       - 1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f
    };
    try { m_pTerrain = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Terran3 failed to allocate on heap." );
        return false;
    }
    m_pTerrain->CreateMesh( vertices3, 36 );
    m_pTerrain->m_model = glm::mat4( 1.0f );
    m_pTerrain->m_model = glm::translate( m_pTerrain->m_model, glm::vec3( 0.0f, -5.0f, 250.0f ) );
    m_pTerrain->m_model = glm::scale( m_pTerrain->m_model, glm::vec3( 1000.0f, 1000.0f, 1000.0f ) );

    return true;
}

void UpdateTempAssets() {
    // Update Objects
    static float angle = 360.0f / 3.141565f;
    m_pSquare->m_model = glm::mat4( 1.0f );
    m_pSquare->m_model = glm::translate( m_pSquare->m_model, glm::vec3( -1.0f, 0.0f, -4.0f ) );
    m_pSquare->m_model = glm::scale( m_pSquare->m_model, glm::vec3( 2.0f, 2.0f, 2.0f ) );
    m_pSquare->m_model = glm::rotate( m_pSquare->m_model, angle, glm::vec3( 0.1f, -0.5f, 1.0f ) );
    angle += 0.01f / 3.141565f * TheEngine::Instance()->m_pTimer->GetDeltaTime();
    if( angle >= 360.0f ) angle = 0.0f;
}

void RenderTempAssets() {
    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_projection", TheEngine::Instance()->m_pCamera->m_projection, true );
    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_view", TheEngine::Instance()->m_pCamera->CalculateViewMatrix(), true );

    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_model", m_pPyramid->m_model, true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_lightColor", glm::vec3( 1.0f, 1.0f, 1.0f ), true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_objectColor", glm::vec3( 1.0f, 0.5f, 0.31f ), true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_lightPos", glm::vec3( 12.5f, 50.0f, 75.0f ), true );
    m_pPyramid->RenderMesh();

    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_model", m_pSquare->m_model, true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_objectColor", glm::vec3( 0.9f, 0.0f, 0.0f ), true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_lightColor", glm::vec3( 1.0f, 1.0f, 1.0f ), true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_lightPos", glm::vec3( 12.5f, 50.0f, 75.0f ), true );
    m_pSquare->RenderMesh();

    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_model", m_pTerrain->m_model, true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_objectColor", glm::vec3( 0.0f, 0.5f, 0.1f ), true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_lightColor", glm::vec3( 1.0f, 1.0f, 1.0f ), true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_lightPos", glm::vec3( 12.5f, 50.0f, 75.0f ), true );
    m_pTerrain->RenderMesh();

    ResourceManager::GetShader( "Light" )->SetMat4( "u_projection", TheEngine::Instance()->m_pCamera->m_projection, true );
    ResourceManager::GetShader( "Light" )->SetMat4( "u_view", TheEngine::Instance()->m_pCamera->CalculateViewMatrix(), true );
    m_pLight->m_model = glm::mat4( 1.0f );
    m_pLight->m_model = glm::translate( m_pLight->m_model, glm::vec3( 12.5f, 50.0f, 75.0f ) );
    m_pLight->m_model = glm::scale( m_pLight->m_model, glm::vec3( 10.0f, 10.0f, 10.0f ) );
    ResourceManager::GetShader( "Light" )->SetMat4( "u_model", m_pLight->m_model, true );
    ResourceManager::GetShader( "Light" )->SetVec3( "u_lightColor", glm::vec3( 1.0f, 1.0f, 1.0f ), true );
    m_pLight->RenderMesh();
}

void CleanTempAssets() {
    if( m_pPyramid != nullptr ) {
        m_pPyramid->Clean();
        delete m_pPyramid;
        m_pPyramid = nullptr;
    }
    if( m_pSquare != nullptr ) {
        m_pSquare->Clean();
        delete m_pSquare;
        m_pSquare = nullptr;
    }
    if( m_pTerrain != nullptr ) {
        m_pTerrain->Clean();
        delete m_pTerrain;
        m_pTerrain = nullptr;
    }
    if( m_pLight != nullptr ) {
        m_pLight->Clean();
        delete m_pLight;
        m_pLight = nullptr;
    }
}

#endif