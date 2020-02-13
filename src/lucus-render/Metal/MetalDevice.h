//
//  MetalDevice.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 12/02/2020.
//

#ifndef _METAL_DEVICE_H
#define _METAL_DEVICE_H

#include <Metal/MTLDevice.h>
#include <Metal/MTLCommandQueue.h>

namespace LucusEngine
{
    class MetalRenderSystem;

    struct MetalDevice
    {
        MetalDevice(MetalRenderSystem* renderSystem);
        ~MetalDevice();
        
        void Init();
        
        id<MTLDevice> mDevice;
        id<MTLCommandQueue> mCommandQueue;
        
        MetalRenderSystem* mRenderSystem;
    };
}

#endif /* _METAL_DEVICE_H */
