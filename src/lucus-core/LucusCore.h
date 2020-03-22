//
//  LucusGame
//
//  Created by Alexander Kardakov
//

#ifndef _LUCUS_ENGINE_CORE_H
#define _LUCUS_ENGINE_CORE_H

#include "LucusTypes.h"
#include "LucusSingleton.h"

#include "LucusFileSystem.h"
#include "LucusImageFormatManager.h"
#include "LucusMeshFormatManager.h"

namespace LucusEngine
{
    class World;
    class RenderSystem;
    class TimeManager;

	class Core : public Singleton<Core>
	{
	public:
		Core();
		~Core();
        
        void LoadModules();
        void UnloadModules();
        
        void SetRenderSystem(RenderSystem* system);
        
        void ChangeViewportSize(u32 width, u32 height);
        
        void StartCoreLoop();
        void Run();
        
        void Tick();
        
    public:
        static Core& Get();
        static Core* GetPtr();
        
        static FileSystem* GetFileSystem();
        static ImageFormatManager* GetImageFormatMgr();
        static MeshFormatManager* GetMeshFormatMgr();
        static RenderSystem* GetRenderSystem();
        static TimeManager* GetTimeManager();

	protected:
        bool mIsActive = false;
		
        RenderSystem* mActiveRenderSystem;
        
        FileSystem* mFileSystem;
        ImageFormatManager* mImageFormatManager;
        MeshFormatManager* mMeshFormatManager;
        TimeManager* mTimeManager;
        World* mWorld;
        
    protected:
        float mTimeStep;
        u32 mMaxStepSim;
	};
}

#endif //_LUCUS_ENGINE_CORE_H
