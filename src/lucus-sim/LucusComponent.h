//
//  LucusComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#ifndef _LUCUS_ENGINE_COMPONENT_H
#define _LUCUS_ENGINE_COMPONENT_H

#include "LucusTypes.h"
#include "LucusTransform.h"

namespace LucusEngine
{
    class ComponentProxy;

    class Component
    {
    public:
        Component();
        virtual ~Component();

        Transform& GetTransform() { return mTransform; }
        
        ComponentProxy* Proxy;
        
//        virtual ComponentProxy* CreateProxy();

    protected:
    	Transform mTransform;
    };
}

#endif /* _LUCUS_ENGINE_COMPONENT_H */
