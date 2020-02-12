
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
    
//    if (mActiveRenderSystem != nullptr)
//    {
//        mActiveRenderSystem->InitWindow();
//    }
}

void Core::Render()
{
    if (mActiveRenderSystem != nullptr)
    {
        mActiveRenderSystem->Render();
    }
}
