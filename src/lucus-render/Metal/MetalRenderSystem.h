//
//  MetalRenderSystem.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 10/02/2020.
//

#ifndef _METAL_RENDER_SYSTEM_H
#define _METAL_RENDER_SYSTEM_H

#include "LucusRenderSystem.h"
#include "MetalView.h"

#include <Metal/MTLDevice.h>
#include <Metal/MTLCommandQueue.h>


namespace LucusEngine
{
    class MetalRenderSystem: public RenderSystem
    {
    public:
		MetalRenderSystem();
		virtual ~MetalRenderSystem();
        
        virtual void Init() override;
        virtual void Render() override;
        
        void RegisterView(MetalView* view);
    
        id<MTLDevice> mDevice;
        id<MTLCommandQueue> mCommandQueue;
        
    protected:
        MetalView* mView;
        
        bool mSystemReady = false;
    };
}

#endif /* _METAL_RENDER_SYSTEM_H */
