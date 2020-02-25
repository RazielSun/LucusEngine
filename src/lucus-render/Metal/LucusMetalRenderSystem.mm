//
//  MetalRenderSystem.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 10/02/2020.
//

#include "LucusMetalRenderSystem.h"
#include "LucusShaderTypes.h"

// temp
#include "LucusMesh.h"
#include "Metal/MTLVertexDescriptor.h"

using namespace LucusEngine;

MetalRenderSystem::MetalRenderSystem() : mDevice(this)
{
}

MetalRenderSystem::~MetalRenderSystem()
{
    if (mMesh)
    {
        delete mMesh;
        mMesh = nullptr;
    }
}

RenderWindow* MetalRenderSystem::CreateRenderWindow(u32 width, u32 height)
{
    mDevice.Init();
    
    mWindow = new MetalWindow(width, height, &mDevice);
    
    mWindows.push_back(static_cast<RenderWindow*>(mWindow));
    
//    CreateBuffers();
    
    return mWindows.front();//static_cast<RenderWindow*>(mWindow);
}

void MetalRenderSystem::CreateBuffers()
{
    // Create Assets
    
    // Mesh
    mMesh = new LucusEngine::Mesh();
    mMesh->Load("Assets/meshes/cube.fbx");
    
    // Create Buffers
    const VectorVertices* vertices = mMesh->GetVertices();
    NSUInteger verticesLength = vertices->size() * sizeof(SimpleVertex); // bytes
    mVerticesBuf = [mDevice.mDevice newBufferWithBytes:vertices->data() length:verticesLength options:MTLResourceOptionCPUCacheModeDefault];
//    memcpy()
    
    const VectorIndices* indices = mMesh->GetIndices();
    NSUInteger indicesLength = indices->size() * sizeof(TriangleIndex); // bytes
    mIndicesBuf = [mDevice.mDevice newBufferWithBytes:indices->data() length:indicesLength options:MTLResourceOptionCPUCacheModeDefault];
    
    mIndicesCount = indicesLength / sizeof(u32); // indices count
    
    MTLVertexDescriptor* vertexDescr = [[MTLVertexDescriptor alloc] init];
    vertexDescr.attributes[0].format = MTLVertexFormatFloat3;
    vertexDescr.attributes[0].bufferIndex = 0;
    vertexDescr.attributes[0].offset = 0;
    
    vertexDescr.layouts[0].stride = sizeof(SimpleVertex);
    vertexDescr.layouts[0].stepRate = 1;
    vertexDescr.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
    
    // Load all the shader files with a .metal file extension in the project.
    id<MTLLibrary> defaultLibrary = [mDevice.mDevice newDefaultLibrary];
        
    //    id<MTLFunction> vertexFunction = [defaultLibrary newFunctionWithName:@"defaultVertexShader"];
    //    id<MTLFunction> fragmentFunction = [defaultLibrary newFunctionWithName:@"defaultFragmentShader"];
        
    id<MTLFunction> vertexFunction = [defaultLibrary newFunctionWithName:@"simpleVertexShader"];
    id<MTLFunction> fragmentFunction = [defaultLibrary newFunctionWithName:@"simpleFragmentShader"];
    
    // Configure a pipeline descriptor that is used to create a pipeline state.
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.label = @"Default Pipeline";
    pipelineStateDescriptor.vertexFunction = vertexFunction;
    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = mWindow->mView.colorPixelFormat;
    pipelineStateDescriptor.vertexDescriptor = vertexDescr;
    
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
//    static const DefaultVertex quad[] =
//    {
//        // 2D Position      // Color
//        { { -0.5, -0.5 },   { 0, 1, 1, 1 } },
//        { { 0.5, -0.5 },    { 1, 1, 0, 1 } },
//        { { 0.5, 0.5 },     { 0, 1, 0, 1 } },
//        { { -0.5, -0.5 },   { 1, 0, 1, 1 } },
//        { { 0.5, 0.5 },     { 0, 0, 1, 1 } },
//        { { -0.5, 0.5 },    { 1, 1, 1, 1 } }
//    };
    
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
            
//            [renderEncoder setVertexBytes:quad length:sizeof(quad) atIndex:0];
//            [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:6];
            
            [renderEncoder setVertexBuffer:mVerticesBuf offset:0 atIndex:0];
//            [renderEncoder setFragmentBuffer:mVerticesBuf offset:0 atIndex:0];
            [renderEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle indexCount:mIndicesCount indexType:MTLIndexTypeUInt32 indexBuffer:mIndicesBuf indexBufferOffset:0];
            
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
