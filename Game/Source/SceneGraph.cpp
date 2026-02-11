#include "SceneGraph.h"

#include "Engine.h"
#include "OpenGL/Mesh.h"
#include "OpenGL/Texture.h"
#include "OpenGL/ResourceManager.h"
#include "ModernLogger.h"

#include <GL/glew.h>
#include <new>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Meshes.h"

#define XDIMTESTCUBES 40
#define YDIMTESTCUBES 40
#define ZDIMTESTCUBES 40

/* These are temporary functions and assets that will eventually be removed.*/
/* Same with the assets being global. */
Mesh *g_pPyramid;
Mesh *g_pGround;
Mesh *g_pLight;
Mesh *g_pCube[XDIMTESTCUBES * YDIMTESTCUBES * ZDIMTESTCUBES];
Texture *g_pContainer;
Texture *g_pContainerSpecular;

bool SetupTempAssets() {
    g_pGround = nullptr;
    g_pPyramid = nullptr;
    g_pLight = nullptr;

    for( int i = 0; i < XDIMTESTCUBES * YDIMTESTCUBES * ZDIMTESTCUBES; i++ ) {
        g_pCube[i] = nullptr;
    }

    for( int z = 0; z < ZDIMTESTCUBES; z++ ) {
        for( int y = 0; y < YDIMTESTCUBES; y++ ) {
            for( int x = 0; x < XDIMTESTCUBES; x++ ) {
                int i = x + XDIMTESTCUBES * y + XDIMTESTCUBES * YDIMTESTCUBES * z;
                g_pCube[i] = new Mesh();
                g_pCube[i]->CreateMesh( vertices2, 216 );

                glm::vec3 spacing( 3.0f, 3.0f, -3.0f );
                glm::vec3 offset( -1.0f * XDIMTESTCUBES / 2.0f * 3.0f, 0.1f, -20.0f );

                glm::vec3 pos = offset + glm::vec3( x * spacing.x,
                    y * spacing.y,
                    z * spacing.z );

                g_pCube[i]->m_model = glm::mat4( 1.0f );
                g_pCube[i]->m_model = glm::translate( g_pCube[i]->m_model, pos );
                g_pCube[i]->m_model = glm::scale( g_pCube[i]->m_model, glm::vec3( 2.0f ) );
            }
        }
    }

    g_pContainer = new Texture();
    g_pContainer->LoadTexture( "Resource/Textures/container2.png" );
    g_pContainerSpecular = new Texture();
    g_pContainerSpecular->LoadTexture( "Resource/Textures/container2_specular.png" );

    ResourceManager::LoadShader( "Resource/Shaders/Light.glsl", "Light" ); // Light
    ResourceManager::LoadShader( "Resource/Shaders/PhongLighting.glsl", "PhongLighting" ); // Phong Lighting = Diffuse + Ambient + Specular

    try { g_pPyramid = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheMLogger::Instance()->Error( "ERROR: MEMORY ALLOCATION: Pyramid failed to allocate on heap." );
        return false;
    }
    g_pPyramid->CreateMesh( vertices, 108 );
    g_pPyramid->m_model = glm::mat4( 1.0f );
    g_pPyramid->m_model = glm::translate( g_pPyramid->m_model, glm::vec3( 1.0f, 1.0f, -1.5f ) );

    try { g_pLight = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheMLogger::Instance()->Error( "ERROR: MEMORY ALLOCATION: Light failed to allocate on heap." );
        return false;
    }
    g_pLight->CreateMesh( vertices2, 216 );
    g_pLight->m_model = glm::mat4( 1.0f );
    g_pLight->m_model = glm::translate( g_pLight->m_model, glm::vec3( 60.0f, 50.0f, -5.0f ) );
    g_pLight->m_model = glm::scale( g_pLight->m_model, glm::vec3( 10.0f, 10.0f, 10.0f ) );

    try { g_pGround = new Mesh(); }
    catch( const std::bad_alloc &e ) {
        (void)e;
        TheMLogger::Instance()->Error( "ERROR: MEMORY ALLOCATION: Ground failed to allocate on heap." );
        return false;
    }
    g_pGround->CreateMesh( vertices3, 36 );
    g_pGround->m_model = glm::mat4( 1.0f );
    g_pGround->m_model = glm::translate( g_pGround->m_model, glm::vec3( 0.0f, -5.0f, 250.0f ) );
    g_pGround->m_model = glm::scale( g_pGround->m_model, glm::vec3( 1000.0f, 1000.0f, 1000.0f ) );

    return true;
}

void UpdateTempAssets() {
    // Update Objects
    static float angle = 360.0f / 3.141565f;

    g_pPyramid->m_model = glm::mat4( 1.0f );
    g_pPyramid->m_model = glm::translate( g_pPyramid->m_model, glm::vec3( 1.0f, 1.0f, -1.5f ) );
    g_pPyramid->m_model = glm::rotate( g_pPyramid->m_model, angle * 0.1f, glm::vec3( 0.0f, 1.0f, 0.0f ) );

    for( int z = 0; z < ZDIMTESTCUBES; z++ ) {
        for( int y = 0; y < YDIMTESTCUBES; y++ ) {
            for( int x = 0; x < XDIMTESTCUBES; x++ ) {
                int i = x + XDIMTESTCUBES * y + XDIMTESTCUBES * YDIMTESTCUBES * z;

                glm::vec3 spacing( 3.0f, 3.0f, -3.0f );
                glm::vec3 offset( -1.0f * XDIMTESTCUBES / 2.0f * 3.0f, 0.1f, -20.0f );

                glm::vec3 pos = offset + glm::vec3( x * spacing.x,
                    y * spacing.y,
                    z * spacing.z );

                g_pCube[i]->m_model = glm::mat4( 1.0f );
                g_pCube[i]->m_model = glm::translate( g_pCube[i]->m_model, pos );
                g_pCube[i]->m_model = glm::scale( g_pCube[i]->m_model, glm::vec3( 2.0f ) );
                g_pCube[i]->m_model = glm::rotate( g_pCube[i]->m_model, angle * 0.5f, glm::vec3( 0.1f, -0.5f, 1.0f ) );
            }
        }
    }

    angle += 0.05f / 3.141565f * TheEngine::Instance()->m_pTimer->GetDeltaTime();
    if( angle >= 360.0f ) angle = 0.0f;
}

void RenderTempAssets() {
    // Light - NOTE: Do light first so can give position to other objects
    ResourceManager::GetShader( "Light" )->SetMat4( "u_projection", TheEngine::Instance()->m_pCamera->m_projection, true );
    ResourceManager::GetShader( "Light" )->SetMat4( "u_view", TheEngine::Instance()->m_pCamera->CalculateViewMatrix() );
    ResourceManager::GetShader( "Light" )->SetMat4( "u_model", g_pLight->m_model );
    ResourceManager::GetShader( "Light" )->SetVec3( "u_lightColor", 1.0f, 1.0f, 1.0f );
    g_pLight->RenderMesh();

    // Set once and let be used the entire frame...
    ResourceManager::GetShader( "PhongLighting" )->SetMat4( "u_projection", TheEngine::Instance()->m_pCamera->m_projection, true );
    ResourceManager::GetShader( "PhongLighting" )->SetMat4( "u_view", TheEngine::Instance()->m_pCamera->CalculateViewMatrix() );
    ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_viewPos", TheEngine::Instance()->m_pCamera->GetCameraPosition() );
    ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_light.position", glm::vec3( g_pLight->m_model[3] ) );
    ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_light.ambient", 0.2f, 0.2f, 0.2f );
    ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_light.diffuse", 1.0f, 1.0f, 1.0f );
    ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_light.specular", 1.0f, 1.0f, 1.0f );

    // Pyramid
    ResourceManager::GetShader( "PhongLighting" )->SetMat4( "u_model", g_pPyramid->m_model, true );
    ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_material.ambient", 1.0f, 0.5f, 0.31f );
    ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_material.diffuse", 1.0f, 0.5f, 0.31f );
    ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_material.specular", 0.5f, 0.5f, 0.5f );
    ResourceManager::GetShader( "PhongLighting" )->SetFloat( "u_material.shininess", 32.0f );
    g_pPyramid->RenderMesh();

    // Test Cubes
    for( int i = 0; i < XDIMTESTCUBES * YDIMTESTCUBES * ZDIMTESTCUBES; i++ ) {
        ResourceManager::GetShader( "PhongLighting" )->SetMat4( "u_model", g_pCube[i]->m_model, true );
        ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_material.ambient", 0.9f, 0.0f, 0.0f );
        ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_material.diffuse", 1.0f, 0.0f, 0.0f );
        ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_material.specular", 0.9f, 0.1f, 0.1f );
        ResourceManager::GetShader( "PhongLighting" )->SetFloat( "u_material.shininess", 100.0f );
        g_pCube[i]->RenderMesh();
    }


    // Ground
    ResourceManager::GetShader( "PhongLighting" )->SetMat4( "u_model", g_pGround->m_model, true );
    ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_material.ambient", 0.0f, 0.2f, 0.5f );
    ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_material.diffuse", 57.0f / 255.0f, 240 / 255.0f, 0.0f );
    ResourceManager::GetShader( "PhongLighting" )->SetVec3( "u_material.specular", 0.3f, 0.3f, 0.3f );
    ResourceManager::GetShader( "PhongLighting" )->SetFloat( "u_material.shininess", 2.0f );
    g_pGround->RenderMesh();
}

void CleanTempAssets() {
    if( g_pPyramid != nullptr ) {
        g_pPyramid->Clean();
        delete g_pPyramid;
        g_pPyramid = nullptr;
    }

    for( int i = 0; i < XDIMTESTCUBES; i++ ) {
        //for( int i = 0; i < XDIMTESTCUBES; i++ ) {
        if( g_pCube[i] != nullptr ) {
            g_pCube[i]->Clean();
            delete g_pCube[i];
            g_pCube[i] = nullptr;
        }
    }
    if( g_pGround != nullptr ) {
        g_pGround->Clean();
        delete g_pGround;
        g_pGround = nullptr;
    }
    if( g_pLight != nullptr ) {
        g_pLight->Clean();
        delete g_pLight;
        g_pLight = nullptr;
    }
}
