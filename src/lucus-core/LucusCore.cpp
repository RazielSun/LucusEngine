
#include "LucusCore.h"

using namespace LucusEngine;

template<> Core* Singleton<Core>::mInstance = 0;

Core::Core()
{
    //
}

Core::~Core()
{
    //
}

Core& Core::Get()
{
    return *mInstance;
}

Core* Core::GetPtr()
{
    return mInstance;
}

void Core::SetRenderSystem(RenderSystem* system)
{
    mActiveRenderSystem = system;
}

void Core::ChangeViewportSize(u32 width, u32 height)
{
    // change viewport size for render system and viewport
}

void Core::Tick()
{
    if (mActiveRenderSystem != nullptr)
    {
        mActiveRenderSystem->Render();
    }
}

void Core::StartCoreLoop()
{
    mIsActive = true;
    
    while(mIsActive)
    {
        if (mActiveRenderSystem != nullptr)
        {
            mActiveRenderSystem->Render();
        }
    }
}
