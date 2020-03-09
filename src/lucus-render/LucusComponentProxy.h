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
#include "LucusTransform.h"

namespace LucusEngine
{
    class Mesh;

    class ComponentProxy
    {
    public:
        ComponentProxy();
        ~ComponentProxy();
        
        virtual void CreateBuffers(const Mesh* mesh) = 0;
        virtual void UpdateUniforms(const Uniforms& uniforms, const Transform& transform) = 0;
    };
}

#endif /* _LUCUS_ENGINE_COMPONENT_PROXY_H */
