//
//  MetalRenderSystem.h
//  LucusGame
//
//  Created by Alexander Kardakov on 10/02/2020.
//

#ifndef _LUCUS_ENGINE_METAL_RENDER_SYSTEM_H
#define _LUCUS_ENGINE_METAL_RENDER_SYSTEM_H

#include "LucusRenderSystem.h"
#include "LucusMetalWindow.h"
#include "LucusMetalDevice.h"

#include <Metal/MTLRenderPipeline.h>
#include <Metal/MTLDepthStencil.h>

namespace LucusEngine
{
    class MetalRenderSystem: public RenderSystem
    {
    public:
		MetalRenderSystem();
		virtual ~MetalRenderSystem();
        
        virtual RenderWindow* CreateRenderWindow(u32 width, u32 height) override;
        virtual void CreateBuffers() override;
        
        virtual void PreRender() override;
        virtual void Render() const override;
        
    protected:
        MetalWindow* mWindow;
        
        MetalDevice mDevice;
        
        id<MTLRenderPipelineState> mPipelineState;
        id<MTLDepthStencilState> mDSState;
    };
}

#endif /* _METAL_RENDER_SYSTEM_H */
