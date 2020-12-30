
#include "LucusCore.h"
#include "LucusMemoryManager.h"

#include "LucusFileSystem.h"
#include "LucusResourceManager.h"
#include "LucusImageFormatManager.h"
#include "LucusMeshFormatManager.h"
#include "LucusTimeManager.h"
#include "LucusLuaState.h"
#include "LucusLuaFactory.h"

#include "LucusRenderSystem.h"
#include "LucusWorld.h"

#include "LucusActor.h"

#include <cmath>

using namespace LucusEngine;

template<> Core* Singleton<Core>::mInstance = nullptr;

Core::Core() :
    mTimeStep(1.0f / 60.0f),
    mMaxStepSim(5),
    bTickTime(false)
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
    mMemoryManager = new MemoryManager();

    mFileSystem = mMemoryManager->NewOnModule<FileSystem>();
    mResourceManager = mMemoryManager->NewOnModule<ResourceManager>();
    mImageFormatManager = mMemoryManager->NewOnModule<ImageFormatManager>();
    mMeshFormatManager = mMemoryManager->NewOnModule<MeshFormatManager>();
    mTimeManager = mMemoryManager->NewOnModule<TimeManager>();
    mLuaState = mMemoryManager->NewOnModule<LuaState>();
    // mFileSystem = new FileSystem();
    // mResourceManager = new ResourceManager();
    // mImageFormatManager = new ImageFormatManager();
    // mMeshFormatManager = new MeshFormatManager();
    // mTimeManager = new TimeManager();
}

void Core::UnloadModules()
{
    mFileSystem->~FileSystem();
    mResourceManager->~ResourceManager();
    mImageFormatManager->~ImageFormatManager();
    mMeshFormatManager->~MeshFormatManager();
    mTimeManager->~TimeManager();
    mLuaState->~LuaState();
    // delete mFileSystem;
    // delete mResourceManager;
    // delete mImageFormatManager;
    // delete mMeshFormatManager;
    // delete mTimeManager;

    delete mMemoryManager;
}

Core& Core::Get()
{
    return *mInstance;
}

Core* Core::GetPtr()
{
    return mInstance;
}

MemoryManager* Core::GetMemoryManager()
{
    return Core::Get().mMemoryManager;
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

void Core::Run()
{
    CreateWorld();
    
    if (mLuaState != nullptr)
    {
        mLuaState->Do();
    }
    
    bTickTime = true;
}

void Core::Tick()
{
    if (bTickTime)
    {
        mTimeManager->UpdateTime();
        float deltaSeconds = mTimeManager->GetDeltaSeconds();
        
        if (mWorld != nullptr)
        {
            for (u32 i = 0; i < mMaxStepSim && deltaSeconds > mTimeStep; ++i)
            {
                mWorld->Tick(mTimeStep);
                deltaSeconds -= mTimeStep;
            }
        }
        else
        {
            float val = std::fmodf(deltaSeconds, mTimeStep);
            deltaSeconds -= static_cast<int>(val)*mTimeStep;
        }
        
        
        // calculate how close or far we are from the next timestep
    //    auto alpha = (float) lag.count() / timestep.count();
    //    auto interpolated_state = interpolate(current_state, previous_state, alpha);
        if (mActiveRenderSystem != nullptr)
        {
            mActiveRenderSystem->PreRender();
            mActiveRenderSystem->Render();
        }
        
        mTimeManager->SetUnusedSeconds(deltaSeconds);
    }
    
}

//void Core::StartCoreLoop()
//{
//    mIsActive = true;
//
//    while(mIsActive)
//    {
//        if (mActiveRenderSystem != nullptr)
//        {
//            mActiveRenderSystem->Render();
//        }
//    }
//}

void Core::CreateWorld()
{
    mWorld = mMemoryManager->NewOnModule<World>();
    if (nullptr != mWorld)
    {
        mWorld->InitWorld();
        LuaFactory<World>::RegisterGlobal(mLuaState, mWorld);
        LuaFactory<Actor>::RegisterClass(mLuaState);
        //        LuaRegisterGlobal<LucusEngine::Core>(*mLuaState);
    }
}
