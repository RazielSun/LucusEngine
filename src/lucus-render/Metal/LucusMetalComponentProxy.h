//
//  LucusMetalComponentProxy.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 09/03/2020.
//

#ifndef _LUCUS_ENGINE_METAL_COMPONENT_PROXY_H
#define _LUCUS_ENGINE_METAL_COMPONENT_PROXY_H

#include "LucusSceneComponentProxy.h"

#include <Metal/MTLBuffer.h>
#include <Metal/MTLTexture.h>
#include <Metal/MTLRenderCommandEncoder.h>

namespace LucusEngine
{
    class MetalDevice;
    
    class MetalComponentProxy : public SceneComponentProxy
    {
    public:
        MetalComponentProxy(MetalDevice* ownerDevice);
        ~MetalComponentProxy();
        
        virtual void CreateBuffers(Mesh* mesh) override;
        virtual void CreateTexture(Image* image) override;
        virtual void UpdateUniforms(const Uniforms& uniforms, SceneComponent* component) override;
        
        void DrawIndexed(id<MTLRenderCommandEncoder> encoder);
        
    protected:
        MetalDevice* mOwnerDevice;
        
        id<MTLBuffer> mVerticesBuf;
        id<MTLBuffer> mIndicesBuf;
        NSUInteger mIndicesCount;
        id<MTLBuffer> mUniforms;

        id<MTLTexture> mTexture;
    };
}

#endif /* _LUCUS_ENGINE_METAL_COMPONENT_PROXY_H */
