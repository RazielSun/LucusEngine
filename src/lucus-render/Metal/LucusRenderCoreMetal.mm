
#include "LucusRenderCore.h"
#include "LucusCore.h"
#include "LucusMemoryManager.h"
#include "LucusMetalRenderSystem.h"

LucusEngine::RenderSystem* CreateRenderSystem(const std::string& title, u32 width, u32 height)
{
    // Create Render System
    LucusEngine::MetalRenderSystem* renderSystem = LucusEngine::Core::GetMemoryManager()->NewOnModule<LucusEngine::MetalRenderSystem>();
    
    // Create Window
    LucusEngine::RenderWindow* window = renderSystem->CreateRenderWindow(title, width, height);

    return dynamic_cast<LucusEngine::RenderSystem*>(renderSystem);
}
