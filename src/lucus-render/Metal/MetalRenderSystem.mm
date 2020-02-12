//
//  MetalRenderSystem.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 10/02/2020.
//

#include "MetalRenderSystem.h"


using namespace LucusEngine;

MetalRenderSystem::MetalRenderSystem()
{
}

MetalRenderSystem::~MetalRenderSystem()
{
    mView = 0;
	mDevice = 0;
    mCommandQueue = 0;
}

void MetalRenderSystem::Init()
{
    @autoreleasepool {
        mDevice = MTLCreateSystemDefaultDevice();
        mCommandQueue = [mDevice newCommandQueue];
    }
}
        
void MetalRenderSystem::Render()
{
    if (mSystemReady)
    {
        id<MTLCommandBuffer> commandBuffer = [mCommandQueue commandBuffer];
        
        MTLRenderPassDescriptor *descriptor = mView.currentRenderPassDescriptor;
        
        // Create custom render pass descriptor
        //    MTLRenderPassDescriptor *descriptor = [[MTLRenderPassDescriptor alloc] init];
        //    descriptor.colorAttachments[0].texture = view.currentDrawable.texture;
        //    descriptor.colorAttachments[0].clearColor = MTLClearColorMake(1, 0, 0, 1);
        //    descriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
        //    descriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        
        if (descriptor != nil)
        {
            id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:descriptor];
            renderEncoder.label = @"MyRenderEncoder";
            
            [renderEncoder endEncoding];
            
            [commandBuffer presentDrawable:mView.currentDrawable];
        }
        
        [commandBuffer commit];
    }
}

void MetalRenderSystem::RegisterView(MetalView* view)
{
    mView = view;
    
    mSystemReady = mView != nullptr;
}
