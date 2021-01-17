//
//  LucusGame
//
//  Created by Alexander Kardakov
//

#ifndef _LUCUS_ENGINE_CORE_H
#define _LUCUS_ENGINE_CORE_H

#include "LucusTypes.h"
#include "LucusSingleton.h"

namespace LucusEngine
{
    class MemoryManager;
    class FileSystem;
    class ResourceManager;
    class ImageFormatManager;
    class MeshFormatManager;
    class World;
    class RenderSystem;
    class TimeManager;
    class LuaState;

	class Core : public Singleton<Core>
	{
	public:
		Core();
		~Core();
        
        void LoadModules();
        void UnloadModules();
        
        void SetRenderSystem(RenderSystem* system);
        void CreateWorld();

        void CreateLua();
        void RunLua(cc8* path);
        
        void ChangeViewportSize(u32 width, u32 height);
        
        void Run();
        
        void Tick();
        
    public:
        static Core& Get();
        static Core* GetPtr();
        
        static MemoryManager* GetMemoryManager();
        static FileSystem* GetFileSystem();
        static ResourceManager* GetResourceMgr();
        static ImageFormatManager* GetImageFormatMgr();
        static MeshFormatManager* GetMeshFormatMgr();
        static RenderSystem* GetRenderSystem();
        static TimeManager* GetTimeManager();
        
        template <class T>
        static T* GetModule();

	protected:
        bool mIsActive = false;

        MemoryManager* mMemoryManager;
        
        FileSystem* mFileSystem;
        ResourceManager* mResourceManager;
        
        // TODO: move to resource
        ImageFormatManager* mImageFormatManager;
        MeshFormatManager* mMeshFormatManager;

        TimeManager* mTimeManager;
        LuaState* mLuaState;

        RenderSystem* mActiveRenderSystem = nullptr;
        World* mWorld = nullptr;
        
    protected:
        float mTimeStep;
        u32 mMaxStepSim;
        bool bTickTime;
	};

    template <> MemoryManager* Core::GetModule<MemoryManager>();
    template <> FileSystem* Core::GetModule<FileSystem>();
    template <> ResourceManager* Core::GetModule<ResourceManager>();

    template <> ImageFormatManager* Core::GetModule<ImageFormatManager>();
    template <> MeshFormatManager* Core::GetModule<MeshFormatManager>();

    template <> LuaState* Core::GetModule<LuaState>();
    template <> TimeManager* Core::GetModule<TimeManager>();

    template <> World* Core::GetModule<World>();
    template <> RenderSystem* Core::GetModule<RenderSystem>();

    template <> void* Core::GetModule<void>() = delete;
}

#endif //_LUCUS_ENGINE_CORE_H
