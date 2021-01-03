
#include "LucusRenderCore.h"
#include "LucusCore.h"
#include "LucusMemoryManager.h"
#include "LucusD3D12RenderSystem.h"

using namespace Windows::UI::Core;

LucusEngine::RenderSystem* CreateRenderSystem(u32 width, u32 height)
{
    // Create Render System
    LucusEngine::D3D12RenderSystem* renderSystem = LucusEngine::Core::GetMemoryManager()->NewOnModule<LucusEngine::D3D12RenderSystem>();
    
    // Create Window
    renderSystem->SetCoreWindow(CoreWindow::GetForCurrentThread());

    return dynamic_cast<LucusEngine::RenderSystem*>(renderSystem);
}