#ifndef __TEMP__
#define __TEMP__

#include "Engine.h"
#include "OpenGL/Mesh.h"
#include "OpenGL/ResourceManager.h"
//#include "OpenGL/Terrain.h"
#include "ModernLogger.h"
#include "RandomGenerator.h"

#include <GL/glew.h>
#include <new>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* These are temporary functions and assets that will eventually be removed.*/
/* Same with the assets being global. */
//Terrain *m_pTerrain;
Mesh *m_pPyramid;
Mesh *m_pWater;
Mesh *m_pCube;
Mesh *m_pLight;

bool SetupTempAssets();
void UpdateTempAssets();
void RenderTempAssets();

bool SetupTempAssets() {
    m_pWater = nullptr;
    m_pPyramid = nullptr;
    m_pWater = nullptr;
    m_pCube = nullptr;
    m_pLight = nullptr;

    ResourceManager::LoadShader( "Resource/Shaders/Light.glsl", "Light" ); // Light
    ResourceManager::LoadShader( "Resource/Shaders/SimpleLight.glsl", "SimpleLight" ); // Phong Lighting = Diffuse + Ambient + Specular

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
        TheMLogger::Instance()->Error( "ERROR: MEMORY ALLOCATION: Pyramid failed to allocate on heap." );
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
    try { m_pCube = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheMLogger::Instance()->Error( "ERROR: MEMORY ALLOCATION: Cube failed to allocate on heap." );
        return false;
    }
    m_pCube->CreateMesh( vertices2, 216 );

    try { m_pLight = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheMLogger::Instance()->Error( "ERROR: MEMORY ALLOCATION: Light failed to allocate on heap." );
        return false;
    }
    m_pLight->CreateMesh( vertices2, 216 );

    float vertices3[]{
        -1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
       -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f
    };
    try { m_pWater = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        //print_error_message( "ERROR: MEMORY ALLOCATION: Water failed to allocate on heap." );
        return false;
    }
    m_pWater->CreateMesh( vertices3, 36 );
    m_pWater->m_model = glm::mat4( 1.0f );
    m_pWater->m_model = glm::translate( m_pWater->m_model, glm::vec3( 0.0f, -5.0f, 250.0f ) );
    m_pWater->m_model = glm::scale( m_pWater->m_model, glm::vec3( 1000.0f, 1000.0f, 1000.0f ) );


    unsigned char *dataUchar = TheRandomGenerator::Instance()->GenerateGridUChar( 128 );
    float *dataf = TheRandomGenerator::Instance()->GenerateGridFloat( 128 );

    //try { m_pTerrain = new Terrain(); }
    //catch( const std::bad_alloc &e ) {
    //    (void)e;
    //    TheMLogger::Instance()->Error( "ERROR: MEMORY ALLOCATION: Terrain failed to allocate on heap." );
    //    return false;
    //}

    return true;
}

void UpdateTempAssets() {
    // Update Objects
    static float angle = 360.0f / 3.141565f;
    m_pCube->m_model = glm::mat4( 1.0f );
    m_pCube->m_model = glm::translate( m_pCube->m_model, glm::vec3( -1.0f, 0.0f, -4.0f ) );
    m_pCube->m_model = glm::scale( m_pCube->m_model, glm::vec3( 2.0f, 2.0f, 2.0f ) );
    m_pCube->m_model = glm::rotate( m_pCube->m_model, angle * 0.5f, glm::vec3( 0.1f, -0.5f, 1.0f ) );
    m_pPyramid->m_model = glm::mat4( 1.0f );
    m_pPyramid->m_model = glm::translate( m_pPyramid->m_model, glm::vec3( 1.0f, 1.0f, -1.5f ) );
    m_pPyramid->m_model = glm::rotate( m_pPyramid->m_model, angle * 0.1f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    angle += 0.005f / 3.141565f * TheEngine::Instance()->m_pTimer->GetDeltaTime();
    if( angle >= 360.0f ) angle = 0.0f;
}

void RenderTempAssets() {
    // Light - NOTE: Do light first so can give position to other objects
    ResourceManager::GetShader( "Light" )->SetMat4( "u_projection", TheEngine::Instance()->m_pCamera->m_projection, true );
    ResourceManager::GetShader( "Light" )->SetMat4( "u_view", TheEngine::Instance()->m_pCamera->CalculateViewMatrix() );
    m_pLight->m_model = glm::mat4( 1.0f );
    m_pLight->m_model = glm::translate( m_pLight->m_model, glm::vec3( 12.5f, 50.0f, 75.0f ) );
    m_pLight->m_model = glm::scale( m_pLight->m_model, glm::vec3( 10.0f, 10.0f, 10.0f ) );
    ResourceManager::GetShader( "Light" )->SetMat4( "u_model", m_pLight->m_model );
    ResourceManager::GetShader( "Light" )->SetVec3( "u_lightColor", 1.0f, 1.0f, 1.0f );
    m_pLight->RenderMesh();

    // Set once and let be used the entire frame...
    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_projection", TheEngine::Instance()->m_pCamera->m_projection, true );
    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_view", TheEngine::Instance()->m_pCamera->CalculateViewMatrix() );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_viewPos", TheEngine::Instance()->m_pCamera->GetCameraPosition() );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_light.position", glm::vec3( m_pLight->m_model[3] ) );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_light.ambient", 0.2f, 0.2f, 0.2f );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_light.diffuse", 1.0f, 1.0f, 1.0f );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_light.specular", 1.0f, 1.0f, 1.0f );

    // Pyramid
    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_model", m_pPyramid->m_model, true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_material.ambient", 1.0f, 0.5f, 0.31f );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_material.diffuse", 1.0f, 0.5f, 0.31f );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_material.specular", 0.5f, 0.5f, 0.5f );
    ResourceManager::GetShader( "SimpleLight" )->SetFloat( "u_material.shininess", 32.0f );
    m_pPyramid->RenderMesh();

    // Rotating Cube
    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_model", m_pCube->m_model, true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_material.ambient", 0.9f, 0.0f, 0.0f );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_material.diffuse", 1.0f, 0.0f, 0.0f );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_material.specular", 0.9f, 0.1f, 0.1f );
    ResourceManager::GetShader( "SimpleLight" )->SetFloat( "u_material.shininess", 100.0f );
    m_pCube->RenderMesh();

    // Water
    ResourceManager::GetShader( "SimpleLight" )->SetMat4( "u_model", m_pWater->m_model, true );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_material.ambient", 0.0f, 0.2f, 0.5f );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_material.diffuse", 0.0f, 0.2f, 0.5f );
    ResourceManager::GetShader( "SimpleLight" )->SetVec3( "u_material.specular", 0.3f, 0.3f, 0.3f );
    ResourceManager::GetShader( "SimpleLight" )->SetFloat( "u_material.shininess", 2.0f );
    m_pWater->RenderMesh();
}

void CleanTempAssets() { 
    if( m_pPyramid != nullptr ) {
        m_pPyramid->Clean();
        delete m_pPyramid;
        m_pPyramid = nullptr;
    }
    if( m_pCube != nullptr ) {
        m_pCube->Clean();
        delete m_pCube;
        m_pCube = nullptr;
    }
    if( m_pWater != nullptr ) {
        m_pWater->Clean();
        delete m_pWater;
        m_pWater = nullptr;
    }
    if( m_pLight != nullptr ) {
        m_pLight->Clean();
        delete m_pLight;
        m_pLight = nullptr;
    }
}

#endif