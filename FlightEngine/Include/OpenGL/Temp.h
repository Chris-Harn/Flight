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

//Mesh *m_pTerran;
//Mesh *m_pTerran2;
//Mesh *m_pTerran3;

bool SetupTempAssets();
void UpdateTempAssets();
void RenderTempAssets();

bool SetupTempAssets() {

    return true;
}

void UpdateTempAssets() {

}

void RenderTempAssets() {
  
}

void CleanTempAssets() {
    //if( m_pTerran != nullptr ) {
    //    m_pTerran->Clean();
    //    delete m_pTerran;
    //    m_pTerran = nullptr;
    //}
    //if( m_pTerran2 != nullptr ) {
    //    m_pTerran2->Clean();
    //    delete m_pTerran2;
    //    m_pTerran2 = nullptr;
    //}
    //if( m_pTerran3 != nullptr ) {
    //    m_pTerran3->Clean();
    //    delete m_pTerran3;
    //    m_pTerran3 = nullptr;
    //}
}

#endif