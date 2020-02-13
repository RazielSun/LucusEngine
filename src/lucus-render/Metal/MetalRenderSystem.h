//
//  MetalRenderSystem.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 10/02/2020.
//

#ifndef _METAL_RENDER_SYSTEM_H
#define _METAL_RENDER_SYSTEM_H

#include "LucusRenderSystem.h"
#include "MetalWindow.h"
#include "MetalDevice.h"

namespace LucusEngine
{
    class MetalRenderSystem: public RenderSystem
    {
    public:
		MetalRenderSystem();
		virtual ~MetalRenderSystem();
        
        virtual Window* CreateWindow(u32 width, u32 height) override;
        virtual void Render() override;
        
    protected:
        MetalWindow* mWindow;
        
        MetalDevice mDevice;
        
//        bool mSystemReady = false;
    };
}

#endif /* _METAL_RENDER_SYSTEM_H */
