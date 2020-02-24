
#include "LucusCore.h"

using namespace LucusEngine;

template<> Core* Singleton<Core>::mInstance = nullptr;

Core::Core()
{
    LoadModules();
}

Core::~Core()
{
    UnloadModules();
    
    mInstance = nullptr;
    
    // remove render system via smartpointer
//    if (mActiveRenderSystem != nullptr)
//    {
//        delete mActiveRenderSystem;
//        mActiveRenderSystem = nullptr;
//    }
}

void Core::LoadModules()
{
    mFileSystem = new FileSystem();
    mMeshFormatManager = new MeshFormatManager();
}

void Core::UnloadModules()
{
    delete mFileSystem;
    delete mMeshFormatManager;
}

Core& Core::Get()
{
    return *mInstance;
}

Core* Core::GetPtr()
{
    return mInstance;
}

FileSystem* Core::GetFileSystem()
{
    return Core::Get().mFileSystem;
}

MeshFormatManager* Core::GetMeshFormatMgr()
{
    return Core::Get().mMeshFormatManager;
}

void Core::SetRenderSystem(RenderSystem* system)
{
    mActiveRenderSystem = system;
    //if (mActiveRenderSystem)
    //{
    //    mActiveRenderSystem->CreateBuffers();
    //}
}

void Core::ChangeViewportSize(u32 width, u32 height)
{
    // change viewport size for render system and viewport
    if (mActiveRenderSystem != nullptr)
    {
        mActiveRenderSystem->ChangeViewportSize(width, height);
    }
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
