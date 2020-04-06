
#include "LucusCore.h"
#include "LucusRenderSystem.h"
#include "LucusWorld.h"
#include "LucusTimeManager.h"

using namespace LucusEngine;

template<> Core* Singleton<Core>::mInstance = nullptr;

Core::Core() :
    mTimeStep(1.0f / 60.0f),
    mMaxStepSim(5)
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
    mResourceManager = new ResourceManager();
    mImageFormatManager = new ImageFormatManager();
    mMeshFormatManager = new MeshFormatManager();
    mTimeManager = new TimeManager();
}

void Core::UnloadModules()
{
    delete mFileSystem;
    delete mResourceManager;
    delete mImageFormatManager;
    delete mMeshFormatManager;
    delete mTimeManager;
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

ResourceManager* Core::GetResourceMgr()
{
    return Core::Get().mResourceManager;
}

ImageFormatManager* Core::GetImageFormatMgr()
{
    return Core::Get().mImageFormatManager;
}

MeshFormatManager* Core::GetMeshFormatMgr()
{
    return Core::Get().mMeshFormatManager;
}

RenderSystem* Core::GetRenderSystem()
{
    return Core::Get().mActiveRenderSystem;
}

TimeManager* Core::GetTimeManager()
{
    return Core::Get().mTimeManager;
}

void Core::SetRenderSystem(RenderSystem* system)
{
    mActiveRenderSystem = system;
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
    mTimeManager->UpdateTime();
    float deltaSeconds = mTimeManager->GetDeltaSeconds();
    
    for (u32 i = 0; i < mMaxStepSim && deltaSeconds > mTimeStep; ++i)
    {
        mWorld->Tick(mTimeStep);
        deltaSeconds -= mTimeStep;
    }
    
    // calculate how close or far we are from the next timestep
//    auto alpha = (float) lag.count() / timestep.count();
//    auto interpolated_state = interpolate(current_state, previous_state, alpha);
    if (mActiveRenderSystem != nullptr)
    {
        mActiveRenderSystem->Render();
    }
    
    mTimeManager->SetUnusedSeconds(deltaSeconds);
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

void Core::CreateWorld(World* world)
{
    mWorld = world;
    if (nullptr != mWorld)
    {
        mWorld->InitWorld();
    }
}
