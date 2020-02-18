//
//  MetalRenderSystem.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 10/02/2020.
//

#include "LucusMetalRenderSystem.h"
#include "LucusShaderTypes.h"

using namespace LucusEngine;

MetalRenderSystem::MetalRenderSystem() : mDevice(this)
{
}

MetalRenderSystem::~MetalRenderSystem()
{
}

RenderWindow* MetalRenderSystem::CreateRenderWindow(u32 width, u32 height)
{
    mDevice.Init();
    
    mWindow = new MetalWindow(width, height, &mDevice);
    
    mWindows.push_back(static_cast<RenderWindow*>(mWindow));
    
    CreateBuffers();
    
    return mWindows.front();//static_cast<RenderWindow*>(mWindow);
}

void MetalRenderSystem::CreateBuffers()
{
    // Create Assets
    
    // Load all the shader files with a .metal file extension in the project.
    id<MTLLibrary> defaultLibrary = [mDevice.mDevice newDefaultLibrary];
    
    id<MTLFunction> vertexFunction = [defaultLibrary newFunctionWithName:@"defaultVertexShader"];
    id<MTLFunction> fragmentFunction = [defaultLibrary newFunctionWithName:@"defaultFragmentShader"];
    
    // Configure a pipeline descriptor that is used to create a pipeline state.
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.label = @"Default Pipeline";
    pipelineStateDescriptor.vertexFunction = vertexFunction;
    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = mWindow->mView.colorPixelFormat;
    
    NSError *error = NULL;
    
    mPipelineState = [mDevice.mDevice newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error];
    
    // Pipeline State creation could fail if the pipeline descriptor isn't set up properly.
    //  If the Metal API validation is enabled, you can find out more information about what
    //  went wrong.  (Metal API validation is enabled by default when a debug build is run
    //  from Xcode.)
//    NSAssert(mPipelineState, @"Failed to created pipeline state: %@", error);
}
        
void MetalRenderSystem::Render()
{
    static const DefaultVertex quad[] =
    {
        // 2D Position      // Color
        { { -0.5, -0.5 },   { 0, 1, 1, 1 } },
        { { 0.5, -0.5 },    { 1, 1, 0, 1 } },
        { { 0.5, 0.5 },     { 0, 1, 0, 1 } },
        { { -0.5, -0.5 },   { 1, 0, 1, 1 } },
        { { 0.5, 0.5 },     { 0, 0, 1, 1 } },
        { { -0.5, 0.5 },    { 1, 1, 1, 1 } }
    };
    
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
            
            [renderEncoder setRenderPipelineState:mPipelineState];
            
            [renderEncoder setVertexBytes:quad length:sizeof(quad) atIndex:0];
            
            [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:6];
            
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

void MetalRenderSystem::ChangeViewportSize(u32 width, u32 height)
{
    for (auto it = mWindows.begin(); it != mWindows.end(); it++)
    {
        (*it)->ChangeViewportSize(width, height);
    }
}
