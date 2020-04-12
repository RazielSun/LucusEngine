//
//  LucusComponentProxy.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#ifndef _LUCUS_ENGINE_COMPONENT_PROXY_H
#define _LUCUS_ENGINE_COMPONENT_PROXY_H

#include "LucusTypes.h"
#include "LucusRenderTypes.h"

namespace LucusEngine
{
    class Mesh;
    class Image;

    class SceneComponent;

    class SceneComponentProxy
    {
    public:
        SceneComponentProxy();
        ~SceneComponentProxy();
        
        virtual void CreateBuffers(Mesh* mesh) = 0;
        virtual void CreateTexture(Image* image) = 0;
        virtual void UpdateUniforms(const Uniforms& uniforms, const SceneComponent* component) = 0;
    };
}

#endif /* _LUCUS_ENGINE_COMPONENT_PROXY_H */
