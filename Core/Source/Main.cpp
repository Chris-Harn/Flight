#include "Engine.h"

#include <iostream>

int main() {
    if( TheEngine::Instance()->Init() == true ) {
        while( TheEngine::Instance()->Running() ) {
            TheEngine::Instance()->HandleEvents();
            TheEngine::Instance()->Render();
        }
    }
    TheEngine::Instance()->Clean();

    return 0;
}