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
Mesh *m_pTerran;
Mesh *m_pTerran2;
Mesh *m_pTerran3;

bool SetupTempAssets();
void UpdateTempAssets();
void RenderTempAssets();

bool SetupTempAssets() {
    m_pTerran = nullptr;
    m_pTerran2 = nullptr;
    m_pTerran3 = nullptr;

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
    m_pTerran->m_model = glm::scale( m_pTerran->m_model, glm::vec3( 2.0f, 2.0f, 2.0f ) );

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

void UpdateTempAssets() {
    // Update Objects
    static float angle = 360.0f / 3.141565f;
    m_pTerran2->m_model = glm::mat4( 1.0f );
    m_pTerran2->m_model = glm::translate( m_pTerran2->m_model, glm::vec3( -1.0f, 0.0f, -4.0f ) );
    m_pTerran2->m_model = glm::scale( m_pTerran2->m_model, glm::vec3( 2.0f, 2.0f, 2.0f ) );
    m_pTerran2->m_model = glm::rotate( m_pTerran2->m_model, angle, glm::vec3( 0.1f, -0.5f, 1.0f ) );
    angle += 0.01f / 3.141565f * TheEngine::Instance()->m_pTimer->GetDeltaTime();
    if( angle >= 360.0f ) angle = 0.0f;
}

void RenderTempAssets() {
    ResourceManager::GetShader( "DrawMesh" )->SetMat4( "projection", TheEngine::Instance()->m_pCamera->m_projection, true );
    ResourceManager::GetShader( "DrawMesh" )->SetMat4( "view", TheEngine::Instance()->m_pCamera->CalculateViewMatrix(), true );

    ResourceManager::GetShader( "DrawMesh" )->SetMat4( "model", m_pTerran->m_model, true );
    m_pTerran->RenderMesh();

    ResourceManager::GetShader( "DrawMesh" )->SetMat4( "model", m_pTerran2->m_model, true );
    m_pTerran2->RenderMesh();

    ResourceManager::GetShader( "DrawMesh" )->SetMat4( "model", m_pTerran3->m_model, true );
    m_pTerran3->RenderMesh();
}

void CleanTempAssets() {
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

#endif