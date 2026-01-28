#include "Engine.h"

int main() {
    if( TheEngine::Instance()->Init() ) {
        while( TheEngine::Instance()->Running() ) {
            TheEngine::Instance()->HandleEvents();
            TheEngine::Instance()->Render();
        }
    }
    TheEngine::Instance()->Clean();

    return 0;
}