//
//  LucusGame
//
//  Created by Alexander Kardakov
//

#ifndef _LUCUS_ENGINE_RENDER_SYSTEM_H
#define _LUCUS_ENGINE_RENDER_SYSTEM_H

#include "LucusTypes.h"
#include "LucusWindow.h"

namespace LucusEngine
{
	class RenderSystem
	{
	public:
		RenderSystem();
		virtual ~RenderSystem();
        
        virtual Window* CreateWindow(u32 width, u32 height) = 0;
        virtual void Render() = 0;

	protected:
        WindowVector mWindows;
	};
}

#endif //_LUCUS_ENGINE_RENDER_SYSTEM_H
