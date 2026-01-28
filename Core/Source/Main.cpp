#include "Main.h"
#include "Engine.h"

int main() {
    if( TheEngine::Instance()->Init( TITLE, RENDER_X_RESOLUTION, RENDER_Y_RESOLUTION, FULL_SCREEN ) ) {
        while( TheEngine::Instance()->Running() ) {
            TheEngine::Instance()->HandleEvents();
            TheEngine::Instance()->Render();
        }
    }
    TheEngine::Instance()->Clean();

    return 0;
}