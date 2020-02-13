//
//  MetalRenderSystem.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 10/02/2020.
//

#include "MetalRenderSystem.h"


using namespace LucusEngine;

MetalRenderSystem::MetalRenderSystem() : mDevice(this)
{
}

MetalRenderSystem::~MetalRenderSystem()
{
}

Window* MetalRenderSystem::CreateWindow(u32 width, u32 height)
{
    mDevice.Init();
    
    mWindow = new MetalWindow(width, height, &mDevice);
    
    mWindows.push_back(static_cast<Window*>(mWindow));
    
    return static_cast<Window*>(mWindow);
}
        
void MetalRenderSystem::Render()
{
//    mWindow->mCurrentDrawable = [mWindow->mView currentDrawable];
    mWindow->mCurrentDrawable = [mWindow->mMetalLayer nextDrawable];
//    if (mSystemReady)
    if (mWindow->mCurrentDrawable != nil)
    {
        id<MTLCommandBuffer> commandBuffer = [mDevice.mCommandQueue commandBuffer];
        
//        MTLRenderPassDescriptor *descriptor = [mWindow->mView currentRenderPassDescriptor];
        
        // Create custom render pass descriptor
        MTLRenderPassDescriptor *descriptor = [[MTLRenderPassDescriptor alloc] init];
        descriptor.colorAttachments[0].texture = mWindow->mCurrentDrawable.texture;
        descriptor.colorAttachments[0].clearColor = MTLClearColorMake(1, 0, 0, 1);
        descriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
        descriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        
        if (descriptor != nil)
        {
            id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:descriptor];
            renderEncoder.label = @"MyRenderEncoder";
            
            [renderEncoder endEncoding];
            
            [commandBuffer presentDrawable:mWindow->mCurrentDrawable]; // mWindow->mView.currentDrawable
        }
        
        [commandBuffer commit];
    }
    else
    {
        // frame aborted
    }
    
    mWindow->mCurrentDrawable = nil;
}
