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

// temp
#include <Metal/MTLBuffer.h>

namespace LucusEngine
{
    class MetalRenderSystem: public RenderSystem
    {
    public:
		MetalRenderSystem();
		virtual ~MetalRenderSystem();
        
        virtual RenderWindow* CreateRenderWindow(u32 width, u32 height) override;
        virtual void CreateBuffers() override;
        virtual void Render() override;
        
    protected:
        MetalWindow* mWindow;
        
        MetalDevice mDevice;
        
        id<MTLRenderPipelineState> mPipelineState;
        
        // temp files for cube
        id<MTLBuffer> mVerticesBuf;
        id<MTLBuffer> mIndicesBuf;
        NSUInteger mIndicesCount;
        id<MTLBuffer> mUniforms;
        
    };
}

#endif /* _METAL_RENDER_SYSTEM_H */
