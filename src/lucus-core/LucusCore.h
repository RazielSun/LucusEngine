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

	protected:
        bool mIsActive = false;

        MemoryManager* mMemoryManager;
        
        FileSystem* mFileSystem;
        ResourceManager* mResourceManager;
        ImageFormatManager* mImageFormatManager;
        MeshFormatManager* mMeshFormatManager;
        TimeManager* mTimeManager;
        LuaState* mLuaState;

        RenderSystem* mActiveRenderSystem;
        World* mWorld;
        
    protected:
        float mTimeStep;
        u32 mMaxStepSim;
        bool bTickTime;
	};
}

#endif //_LUCUS_ENGINE_CORE_H
