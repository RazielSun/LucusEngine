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

namespace LucusEngine
{
	class Core : public Singleton<Core>
	{
	public:
		Core();
		~Core();
        
        static Core& Get();
        static Core* GetPtr();
        
        void SetRenderSystem(RenderSystem* system);
        
        void ChangeViewportSize(u32 width, u32 height);
        
        void StartCoreLoop();
        
        void Tick();

	protected:
        bool mIsActive = false;
		
        RenderSystem* mActiveRenderSystem;
	};
}

#endif //_LUCUS_ENGINE_CORE_H
