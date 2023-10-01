#include "Engine.h"

#include <iostream>

int main( int argc, char *argv[] ) {    
    if( TheEngine::Instance()->Init( "Temp", 800, 600, false ) == true ) {
        while( TheEngine::Instance()->Running() ) {
            TheEngine::Instance()->HandleEvents();
            TheEngine::Instance()->Render();
        }
    }
    TheEngine::Instance()->Clean();

    return 0;
}