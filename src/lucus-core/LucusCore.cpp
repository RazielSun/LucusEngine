
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

#include "lua_bind.h"

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

//    if (mLuaState) mLuaState->~LuaState();
//    if (mActiveRenderSystem) mActiveRenderSystem->~RenderSystem();
//    if (mWorld) mWorld->~World();

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

template <> MemoryManager* Core::GetModule<MemoryManager>() { return Core::Get().mMemoryManager; }
template <> FileSystem* Core::GetModule<FileSystem>() { return Core::Get().mFileSystem; }
template <> ResourceManager* Core::GetModule<ResourceManager>() { return Core::Get().mResourceManager; }

template <> ImageFormatManager* Core::GetModule<ImageFormatManager>() { return Core::Get().mImageFormatManager; }
template <> MeshFormatManager* Core::GetModule<MeshFormatManager>() { return Core::Get().mMeshFormatManager; }

template <> LuaState* Core::GetModule<LuaState>() { return Core::Get().mLuaState; }
template <> TimeManager* Core::GetModule<TimeManager>() { return Core::Get().mTimeManager; }

//template <> World* Core::GetModule<World>() { return Core::Get().mWorld; }
template <> RenderSystem* Core::GetModule<RenderSystem>() { return Core::Get().mActiveRenderSystem; }

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

// void Core::CreateWorld()
// {
//     mWorld = mMemoryManager->NewOnModule<World>();
//     if (nullptr != mWorld)
//     {
//         mWorld->InitWorld();
//     }
// }

void Core::SetWorld(World* world)
{
    if (world != nullptr)
    {
        mWorld = world;
        if (mWorld)
        {
            mWorld->InitWorld();
        }
    }
    else
    {
        mWorld.Reset();
    }
}

//World* Core::GetWorld() const
//{
//    return mWorld.Get();
//}

void Core::CreateLua()
{
    mLuaState = mMemoryManager->NewOnModule<LuaState>();
    if (nullptr != mLuaState)
    {
        mLuaState->RunScript("main.lua");
        BindLua(mLuaState);
        //    if (mWorld) LuaFactory<World>::RegisterGlobal(mLuaState, mWorld);
    }
}

void Core::Run()
{
    mLuaState->Init();
    // Run init func lua
    bTickTime = true;
}

void Core::Tick()
{
    if (bTickTime)
    {
        mTimeManager->UpdateTime();
        float deltaSeconds = mTimeManager->GetDeltaSeconds();
        
        if (mWorld)
        {
            for (u32 i = 0; i < mMaxStepSim && deltaSeconds > mTimeStep; ++i)
            {
                mLuaState->Tick(mTimeStep);
                mWorld->Tick(mTimeStep);
                deltaSeconds -= mTimeStep;
            }
        }
        else
        {
            float val = std::fmodf(deltaSeconds, mTimeStep);
            deltaSeconds -= static_cast<int>(val)*mTimeStep;
        }
        
        if (mWorld)
            mWorld->LateTick();
        
        
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
