//
//  LucusMetalComponentProxy.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 09/03/2020.
//

#include "LucusMetalComponentProxy.h"
#include "LucusTransform.h"
#include "LucusMesh.h"
#include "LucusMetalDevice.h"

using namespace LucusEngine;

MetalComponentProxy::MetalComponentProxy(MetalDevice* ownerDevice) : mOwnerDevice(ownerDevice)
{
    //
}

MetalComponentProxy::~MetalComponentProxy()
{
    mOwnerDevice = nullptr;
}

void MetalComponentProxy::CreateBuffers(Mesh* mesh)
{
    if (nullptr != mesh)
    {
        // Create Buffers
        const VectorVertices* vertices = mesh->GetVertices();
        NSUInteger verticesLength = vertices->size() * sizeof(SimpleVertex); // bytes
        mVerticesBuf = [mOwnerDevice->mDevice newBufferWithBytes:vertices->data() length:verticesLength options:MTLResourceOptionCPUCacheModeDefault];
        
        const VectorIndices* indices = mesh->GetIndices();
        NSUInteger indicesLength = indices->size() * sizeof(TriangleIndex); // bytes
        mIndicesBuf = [mOwnerDevice->mDevice newBufferWithBytes:indices->data() length:indicesLength options:MTLResourceOptionCPUCacheModeDefault];
        
        mIndicesCount = indicesLength / sizeof(u32); // indices count
        
        mUniforms = [mOwnerDevice->mDevice newBufferWithLength:sizeof(Uniforms) options:MTLResourceStorageModeShared];
    }
}

void MetalComponentProxy::UpdateUniforms(const Uniforms& uniforms, const Transform& transform)
{
    memcpy((void*)(mUniforms.contents), &uniforms, sizeof(Uniforms));
    
    // Update Uniforms
    Uniforms* cUniforms = (Uniforms*)(mUniforms.contents);
    
    cUniforms->MODEL_MATRIX = transform.GetModelMatrix().GetNative();
    cUniforms->MVP_MATRIX = matrix_multiply(matrix_multiply(cUniforms->PROJ_MATRIX, cUniforms->VIEW_MATRIX), cUniforms->MODEL_MATRIX);
}

void MetalComponentProxy::DrawIndexed(id<MTLRenderCommandEncoder> renderEncoder)
{
//    [renderEncoder setVertexBytes:quad length:sizeof(quad) atIndex:0];
//    [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:6];

    [renderEncoder setVertexBuffer:mVerticesBuf offset:0 atIndex:0];
//    [renderEncoder setFragmentBuffer:mVerticesBuf offset:0 atIndex:0];

    // only for vertex shader
    [renderEncoder setVertexBuffer:mUniforms offset:0 atIndex:1];
//    [renderEncoder setFragmentBuffer:mUniforms offset:0 atIndex:1];

    [renderEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle indexCount:mIndicesCount indexType:MTLIndexTypeUInt32 indexBuffer:mIndicesBuf indexBufferOffset:0];
                
}
