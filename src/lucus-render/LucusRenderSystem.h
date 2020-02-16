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
	class RenderSystem
	{
	public:
		RenderSystem();
		virtual ~RenderSystem();
        
        virtual RenderWindow* CreateRenderWindow(u32 width, u32 height) = 0;
        virtual void CreateBuffers() = 0;
        virtual void Render() = 0;
        
        virtual void ChangeViewportSize(u32 width, u32 height) = 0;

	protected:
        RenderWindowVector mWindows;
	};
}

#endif //_LUCUS_ENGINE_RENDER_SYSTEM_H
