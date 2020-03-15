//
//  MetalRenderSystem.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 10/02/2020.
//

#include "LucusMetalRenderSystem.h"
#include "LucusRenderTypes.h"
#include "LucusMetalComponentProxy.h"
#include "LucusScene.h"

// temp

#include "LucusMesh.h"
#include "LucusCameraComponent.h"
#include "LucusMeshComponent.h"
#include "Metal/MTLVertexDescriptor.h"


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
    
    return mWindows.front();
}

void MetalRenderSystem::CreateBuffers()
{
    // Create Assets
    for (auto* component : mScene->MeshComps) {
        MetalComponentProxy* proxy = new MetalComponentProxy(&mDevice);
        proxy->CreateBuffers(component->GetMesh());
        component->Proxy = proxy;
    }
    
    MTLVertexDescriptor* vertexDescr = [[MTLVertexDescriptor alloc] init];
    vertexDescr.attributes[0].format = MTLVertexFormatFloat3;
    vertexDescr.attributes[0].bufferIndex = 0;
    vertexDescr.attributes[0].offset = 0;
    
    vertexDescr.layouts[0].stride = sizeof(SimpleVertex);
    vertexDescr.layouts[0].stepRate = 1;
    vertexDescr.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
    
    // Load all the shader files with a .metal file extension in the project.
    id<MTLLibrary> defaultLibrary = [mDevice.mDevice newDefaultLibrary];
        
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
}
        
void MetalRenderSystem::Render()
{
    // Update Uniforms
    Uniforms uniforms;
    CameraComponent* cameraCom = mScene->CameraComp;
    cameraCom->UpdateProjectionMatrix(mWindow->GetViewport());
    uniforms.PROJ_MATRIX = cameraCom->GetProjMatrix().GetNative();
    uniforms.VIEW_MATRIX = cameraCom->GetTransform().GetModelMatrix().GetNative();
    
    for (auto* component : mScene->MeshComps) {
        component->GetTransform().UpdateModelMatrix();
        component->Proxy->UpdateUniforms(uniforms, component->GetTransform());
    }
    
    // Start Frame
    mWindow->mCurrentDrawable = [mWindow->mMetalLayer nextDrawable];
    if (mWindow->mCurrentDrawable != nil)
    {
        id<MTLCommandBuffer> commandBuffer = [mDevice.mCommandQueue commandBuffer];
        
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
            
            for (auto* component : mScene->MeshComps) {
                static_cast<MetalComponentProxy*>(component->Proxy)->DrawIndexed(renderEncoder);
            }

            [renderEncoder endEncoding];
            
            [commandBuffer presentDrawable:mWindow->mCurrentDrawable];
        }
        
        [commandBuffer commit];
    }
    else
    {
        // frame aborted
    }
    
    mWindow->mCurrentDrawable = nil;
}
