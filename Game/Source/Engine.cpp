#include "Engine.h"

#include <iostream>

Engine *Engine::s_pInstance = 0;

Engine::Engine() {
    m_bRunning = false;
}

bool Engine::Init() {
    std::cout << "Flight Version: 0.0.1\n" << std::endl;

    // Everything started up without issue...
    m_bRunning = true;

    return true;
}

void Engine::HandleEvents() {

}

void Engine::Render() {

}

void Engine::Clean() {
    std::cout << "Program ended without issue." << std::endl;
}

bool Engine::Running() {
    return m_bRunning;
}
