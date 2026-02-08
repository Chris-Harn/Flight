#include "OpenGL/Helper.h"

#include "Engine.h"

#include <string>

void DisplayPerformanceInformation() {
    int count = TheEngine::Instance()->m_pTimer->GetFPSValue();
    std::string CurrentFrame = "Display Frequency: " + std::to_string( count );
    CurrentFrame += "\nVSynch: " + std::string( ( TheEngine::Instance()->m_pMainWindow->GetVsync() == true ) ? "True" : "False" );
    CurrentFrame += "\nCap FPS: " + std::string( ( TheEngine::Instance()->m_pTimer->GetRegulationValue() == true ) ? "True" : "False" );
    CurrentFrame += "\nFrame budget: 16.67 ms\nFrame Time: " + std::to_string( 1000.0f / count ) + " ms";
    TheEngine::Instance()->m_pTextRenderer->DrawTextString( CurrentFrame, 25.0f, (float)( TheEngine::Instance()->m_pMainWindow->GetBufferHeight() - 25.0f ), 0.5f, 0.9f, 0.9f, 0.9f );
}