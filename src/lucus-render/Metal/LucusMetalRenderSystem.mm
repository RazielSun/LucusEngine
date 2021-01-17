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
#include "LucusICamera.h"

// temp
#include "Metal/MTLVertexDescriptor.h"

#include "LucusMesh.h"
// #include "LucusCameraComponent.h"
#include "LucusMeshComponent.h"

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
    mWindow->mView.depthStencilPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    mWindow->mView.colorPixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
    mWindow->mView.sampleCount = 1; // No MSAA
    
    // Create Assets
//    for (auto* component : mScene->MeshComps) {
//        MetalComponentProxy* proxy = new MetalComponentProxy(&mDevice);
//        proxy->CreateBuffers(component->GetMesh());
//        proxy->CreateTexture(component->GetImage());
//        component->Proxy = proxy;
//    }
    
    MTLVertexDescriptor* vertexDescr = [[MTLVertexDescriptor alloc] init];
    vertexDescr.attributes[0].format = MTLVertexFormatFloat3;
    vertexDescr.attributes[0].bufferIndex = 0;
    vertexDescr.attributes[0].offset = 0;
    
    vertexDescr.attributes[1].format = MTLVertexFormatFloat2;
    vertexDescr.attributes[1].bufferIndex = 0;
    vertexDescr.attributes[1].offset = 12; // 12 because FVector3 is not simd::float4
    
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
    pipelineStateDescriptor.sampleCount = mWindow->mView.sampleCount;
    pipelineStateDescriptor.vertexFunction = vertexFunction;
    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = mWindow->mView.colorPixelFormat;
    pipelineStateDescriptor.depthAttachmentPixelFormat = mWindow->mView.depthStencilPixelFormat;
    pipelineStateDescriptor.stencilAttachmentPixelFormat = mWindow->mView.depthStencilPixelFormat;
    pipelineStateDescriptor.vertexDescriptor = vertexDescr;
    
    NSError *error = NULL;
    
    mPipelineState = [mDevice.mDevice newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error];
    
    MTLDepthStencilDescriptor *depthStencilDescriptor = [[MTLDepthStencilDescriptor alloc] init];
    depthStencilDescriptor.depthCompareFunction = MTLCompareFunctionLess;
    depthStencilDescriptor.depthWriteEnabled = YES;
    
    mDSState = [mDevice.mDevice newDepthStencilStateWithDescriptor:depthStencilDescriptor];
}

void MetalRenderSystem::PreRender()
{
    RenderSystem::PreRender();
    
    if (mScene != nullptr)
    {
        ICamera* camera = mScene->GetCamera();
        camera->UpdateProjMatrix(mWindow->GetViewport());

        // Udpate Scene Pendings
        for (auto* component : mScene->PendingComponents)
        {
            MeshComponent* meshComp = dynamic_cast<MeshComponent*>(component);
            if (meshComp != nullptr)
            {
                MetalComponentProxy* proxy = new MetalComponentProxy(&mDevice);
                proxy->CreateBuffers(meshComp->GetMesh());
                proxy->CreateTexture(meshComp->GetImage());
                meshComp->Proxy = proxy;
                proxy->Component = component;
                mScene->Proxies.push_back(proxy);
            }
        }
        mScene->PendingComponents.clear();
    }
}
        
void MetalRenderSystem::Render() const
{
    RenderSystem::Render();
    
    if (bSceneEnabled)
    {
        // Update Uniforms
        Uniforms uniforms;
        ICamera* camera = mScene->GetCamera();
        uniforms.PROJ_MATRIX = camera->GetProjMatrix().GetNative();
        uniforms.VIEW_MATRIX = camera->GetViewMatrix().GetNative(); //GetTransform().GetModelMatrix().GetNative();
        
        // for (auto* component : mScene->MeshComps) {
            // component->GetTransform().UpdateMatrices();
            // component->Proxy->UpdateUniforms(uniforms, component);// component->GetTransform());
        // }

        for (auto* proxy : mScene->Proxies)
        {
            proxy->UpdateUniforms(uniforms, proxy->Component);
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
            descriptor.depthAttachment.texture = mWindow->mView.depthStencilTexture;
            descriptor.depthAttachment.storeAction = MTLStoreActionStore;
            descriptor.depthAttachment.loadAction = MTLLoadActionClear;
            descriptor.depthAttachment.clearDepth = 1.0f;
            descriptor.stencilAttachment.texture = mWindow->mView.depthStencilTexture;
            descriptor.stencilAttachment.storeAction = MTLStoreActionStore;
            descriptor.stencilAttachment.loadAction = MTLLoadActionClear;
            descriptor.stencilAttachment.clearStencil = 0;
            
            if (descriptor != nil)
            {
                id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:descriptor];
                renderEncoder.label = @"MyRenderEncoder";
                
                [renderEncoder setFrontFacingWinding:MTLWindingCounterClockwise];//MTLWindingClockwise
                [renderEncoder setCullMode:MTLCullModeBack];
                
                [renderEncoder setRenderPipelineState:mPipelineState];
                [renderEncoder setDepthStencilState:mDSState];
                
                // for (auto* component : mScene->MeshComps) {
                //     static_cast<MetalComponentProxy*>(component->Proxy)->DrawIndexed(renderEncoder);
                // }

                for (auto* proxy : mScene->Proxies)
                {
                    static_cast<MetalComponentProxy*>(proxy)->DrawIndexed(renderEncoder);
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
}
