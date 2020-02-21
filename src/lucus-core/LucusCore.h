//
//  LucusGame
//
//  Created by Alexander Kardakov
//

#ifndef _LUCUS_ENGINE_CORE_H
#define _LUCUS_ENGINE_CORE_H

#include "LucusTypes.h"
#include "LucusSingleton.h"

#include "LucusRenderSystem.h"
#include "LucusFileSystem.h"

namespace LucusEngine
{
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
        
        void Tick();
        
    public:
        static Core& Get();
        static Core* GetPtr();
        
        static FileSystem* GetFileSystem();

	protected:
        bool mIsActive = false;
		
        RenderSystem* mActiveRenderSystem;
        
        FileSystem* mFileSystem;
	};
}

#endif //_LUCUS_ENGINE_CORE_H
