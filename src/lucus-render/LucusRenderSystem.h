//
//  LucusGame
//
//  Created by Alexander Kardakov
//

#ifndef _LUCUS_ENGINE_RENDER_SYSTEM_H
#define _LUCUS_ENGINE_RENDER_SYSTEM_H

namespace LucusEngine
{
	class RenderSystem
	{
	public:
		RenderSystem();
		virtual ~RenderSystem();
        
        virtual void Init() = 0;
        virtual void Render() = 0;

	protected:
		//
	};
}

#endif //_LUCUS_ENGINE_RENDER_SYSTEM_H
