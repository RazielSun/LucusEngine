//
//	LucusRenderSystem.h
//  LucusGame
//
//  Created by Alexander Kardakov
//

#ifndef _LUCUS_ENGINE_RENDER_SYSTEM_H
#define _LUCUS_ENGINE_RENDER_SYSTEM_H

#include "LucusTypes.h"
#include "LucusRenderWindow.h"

namespace LucusEngine
{
	class World;
	class Scene;

	class RenderSystem
	{
	public:
		RenderSystem();
		virtual ~RenderSystem();
        
        virtual RenderWindow* CreateRenderWindow(u32 width, u32 height) = 0;
        virtual void CreateBuffers() = 0;
        
        virtual void PreRender();
        virtual void Render() const;
        
        virtual void ChangeViewportSize(u32 width, u32 height);

        void AllocateScene(World* world);

	protected:
        RenderWindowVector mWindows;
        // RenderWindow* mWindow;

        Scene* mScene;
        bool bSceneEnabled;
	};
}

#endif //_LUCUS_ENGINE_RENDER_SYSTEM_H
