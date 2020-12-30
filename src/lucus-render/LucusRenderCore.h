//
//	LucusRenderCore.h
//  LucusGame
//
//  Created by Alexander Kardakov
//

#ifndef _LUCUS_ENGINE_RENDER_CORE_H
#define _LUCUS_ENGINE_RENDER_CORE_H

#include "LucusTypes.h"

namespace LucusEngine
{
	class RenderSystem;
}

LucusEngine::RenderSystem* CreateRenderSystem(u32 width, u32 height);

#endif //_LUCUS_ENGINE_RENDER_CORE_H