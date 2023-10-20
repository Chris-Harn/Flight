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
//Mesh *m_pTerran3;
//Mesh *m_pLight;

bool SetupTempAssets();
void UpdateTempAssets();
void RenderTempAssets();

bool SetupTempAssets() {
    m_pPyramid = nullptr;
    m_pTerrain = nullptr;
    //m_pTerran3 = nullptr;

    ResourceManager::LoadShader( "Resource/Shaders/SimpleLight.glsl", "SimpleLight" );
    //ResourceManager::LoadShader( "Resource/Shaders/Light.glsl", "Light" );

    // Create a pyramid so we have something temporary to look at
    GLfloat vertices[] = {
        // Bottom Left Square, normals
         0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,
         0.0f,  0.0f,  1.0f,  0.0f,  0.0f, -1.0f,
        -1.0f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f,
        // Bottom Right Square
         0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,
         1.0f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f,
         0.0f,  0.0f,  1.0f,  0.0f,  0.0f, -1.0f,
        // Slope 1
         0.0f,  0.0f,  1.0f,  0.5f,  0.7f,  0.5f,
        -1.0f,  0.0f,  0.0f,  0.5f,  0.7f,  0.5f,
         0.0f,  1.0f,  0.0f,  0.5f,  0.7f,  0.5f,
        // Slope 2
         0.0f,  0.0f, -1.0f, -0.5f,  0.7f, -0.5f,
        -1.0f,  0.0f,  0.0f, -0.5f,  0.7f, -0.5f,
         0.0f,  1.0f,  0.0f, -0.5f,  0.7f, -0.5f,
        // Slope 3
         0.0f,  0.0f, -1.0f,  0.5f,  0.7f, -0.5f,
         1.0f,  0.0f,  0.0f,  0.5f,  0.7f, -0.5f,
         0.0f,  1.0f,  0.0f,  0.5f,  0.7f, -0.5f,
        // Slope 4
         1.0f,  0.0f,  0.0f,  0.5f,  0.7f,  0.5f,
         0.0f,  0.0f,  1.0f,  0.5f,  0.7f,  0.5f,
         0.0f,  1.0f,  0.0f,  0.5f,  0.7f,  0.5f
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

    //// Create a separate triangle for use in the tutorial
    //float vertices2[] = {
    //    // Front Box
    //     0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, // 0
    //     0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, // 1
    //    -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, // 2
    //    -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, // 3
    //    // Back Box
    //     0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, // 4
    //     0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, // 5
    //    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, // 6
    //    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f  // 7
    //};
    //try { m_pTerran2 = new Mesh(); }
    //catch( const std::bad_alloc &e ) {
    //    (void)e;
    //    print_error_message( "ERROR: MEMORY ALLOCATION: Terran2 failed to allocate on heap." );
    //    return false;
    //}
    //m_pTerran2->CreateMesh( vertices2, 48 );

    //try { m_pLight = new Mesh(); }
    //catch( const std::bad_alloc &e ) {
    //    (void)e;
    //    print_error_message( "ERROR: MEMORY ALLOCATION: Light failed to allocate on heap." );
    //    return false;
    //}
    //m_pLight->CreateMesh( vertices2, 48 );

    float vertices3[]{
        -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,   1.0f,
        -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,   1.0f,
         1.0f,  0.0f, -1.0f,  0.0f,  0.0f,   1.0f,
         1.0f,  0.0f,  1.0f,  0.0f,  0.0f,   1.0f
    };
    try { m_pTerrain = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        print_error_message( "ERROR: MEMORY ALLOCATION: Terran3 failed to allocate on heap." );
        return false;
    }
    m_pTerrain->CreateMesh( vertices3, 24 );
    m_pTerrain->m_model = glm::mat4( 1.0f );
    m_pTerrain->m_model = glm::translate( m_pTerrain->m_model, glm::vec3( 0.0f, -5.0f, 250.0f ) );
    m_pTerrain->m_model = glm::scale( m_pTerrain->m_model, glm::vec3( 1000.0f, 1000.0f, 1000.0f ) );

    return true;
}

void UpdateTempAssets() {
    //// Update Objects
    //static float angle = 360.0f / 3.141565f;
    //m_pTerran2->m_model = glm::mat4( 1.0f );
    //m_pTerran2->m_model = glm::translate( m_pTerran2->m_model, glm::vec3( -1.0f, 0.0f, -4.0f ) );
    //m_pTerran2->m_model = glm::scale( m_pTerran2->m_model, glm::vec3( 2.0f, 2.0f, 2.0f ) );
    //m_pTerran2->m_model = glm::rotate( m_pTerran2->m_model, angle, glm::vec3( 0.1f, -0.5f, 1.0f ) );
    //angle += 0.01f / 3.141565f * TheEngine::Instance()->m_pTimer->GetDeltaTime();
    //if( angle >= 360.0f ) angle = 0.0f;
}

void RenderTempAssets() {
    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_projection", TheEngine::Instance()->m_pCamera->m_projection, true );
    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_view", TheEngine::Instance()->m_pCamera->CalculateViewMatrix(), true );

    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_model", m_pPyramid->m_model, true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_lightColor", glm::vec3( 1.0f, 1.0f, 1.0f ), true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_objectColor", glm::vec3( 1.0f, 0.5f, 0.31f ), true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_lightPos", glm::vec3( 20.0, 40.0f, -70.0f ), true );
    m_pPyramid->RenderMesh();

    //ResourceManager::GetShader( "SimpleLight" )->SetMat4( "model", m_pTerran2->m_model, true );
    //ResourceManager::GetShader( "SimpleLight" )->SetVec3( "objectColor", glm::vec3( 1.0f, 0.5f, 0.31f ), true );
    //ResourceManager::GetShader( "SimpleLight" )->SetVec3( "lightColor", glm::vec3( 1.0f, 1.0f, 1.0f ), true );
    //ResourceManager::GetShader( "SimpleLight" )->SetVec3( "lightPos", glm::vec3( 20.0, 40.0f, -70.0f ), true );
    //m_pTerran2->RenderMesh();

    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_model", m_pTerrain->m_model, true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_objectColor", glm::vec3( 0.0f, 0.5f, 0.1f ), true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_lightColor", glm::vec3( 1.0f, 1.0f, 1.0f ), true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_lightPos", glm::vec3( 20.0, 40.0f, -70.0f ), true );
    m_pTerrain->RenderMesh();

    //ResourceManager::GetShader( "Light" )->SetMat4( "projection", TheEngine::Instance()->m_pCamera->m_projection, true );
    //ResourceManager::GetShader( "Light" )->SetMat4( "view", TheEngine::Instance()->m_pCamera->CalculateViewMatrix(), true );
    //m_pLight->m_model = glm::mat4( 1.0f );
    //m_pLight->m_model = glm::translate( m_pLight->m_model, glm::vec3( 20.0, 40.0f, -70.0f ) );
    //m_pLight->m_model = glm::scale( m_pLight->m_model, glm::vec3( 10.0f, 10.0f, 10.0f ) );
    //ResourceManager::GetShader( "Light" )->SetMat4( "model", m_pLight->m_model, true );
    //ResourceManager::GetShader( "Light" )->SetVec3( "lightColor", glm::vec3( 1.0f, 1.0f, 1.0f ), true );
    //m_pLight->RenderMesh();
}

void CleanTempAssets() {
    if( m_pPyramid != nullptr ) {
        m_pPyramid->Clean();
        delete m_pPyramid;
        m_pPyramid = nullptr;
    }
    //if( m_pTerran2 != nullptr ) {
    //    m_pTerran2->Clean();
    //    delete m_pTerran2;
    //    m_pTerran2 = nullptr;
    //}
    if( m_pTerrain != nullptr ) {
        m_pTerrain->Clean();
        delete m_pTerrain;
        m_pTerrain = nullptr;
    }

    //if( m_pLight != nullptr ) {
    //    m_pLight->Clean();
    //    delete m_pLight;
    //    m_pLight = nullptr;
    //}
}

#endif