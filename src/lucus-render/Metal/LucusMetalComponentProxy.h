//
//  LucusMetalComponentProxy.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 09/03/2020.
//

#ifndef _LUCUS_ENGINE_METAL_COMPONENT_PROXY_H
#define _LUCUS_ENGINE_METAL_COMPONENT_PROXY_H

#include "LucusComponentProxy.h"

#include <Metal/MTLBuffer.h>
#include <Metal/MTLRenderCommandEncoder.h>

namespace LucusEngine
{
    class Mesh;
    class Transform;

    class MetalDevice;
    
    class MetalComponentProxy : public ComponentProxy
    {
    public:
        MetalComponentProxy(MetalDevice* ownerDevice);
        ~MetalComponentProxy();
        
        virtual void CreateBuffers(const Mesh* mesh) override;
        virtual void UpdateUniforms(const Uniforms& uniforms, const Transform& transform) override;
        
        void DrawIndexed(id<MTLRenderCommandEncoder> encoder);
        
    protected:
        MetalDevice* mOwnerDevice;
        
        id<MTLBuffer> mVerticesBuf;
        id<MTLBuffer> mIndicesBuf;
        NSUInteger mIndicesCount;
        id<MTLBuffer> mUniforms;
    };
}

#endif /* _LUCUS_ENGINE_METAL_COMPONENT_PROXY_H */
