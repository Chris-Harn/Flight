#include "Main.h"
#include "Engine.h"

#include <iostream>

int main( int argc, char *argv[] ) {    
    if( TheEngine::Instance()->Init( TITLE, X_RESOLUTION, Y_RESOLUTION, FULL_SCREEN ) == true ) {
        while( TheEngine::Instance()->Running() ) {
            TheEngine::Instance()->HandleEvents();
            TheEngine::Instance()->Render();
        }
    }
    TheEngine::Instance()->Clean();

    return 0;
}