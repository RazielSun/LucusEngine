//
//  LucusComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#ifndef _LUCUS_ENGINE_COMPONENT_H
#define _LUCUS_ENGINE_COMPONENT_H

#include "LucusTypes.h"

namespace LucusEngine
{
    class Component
    {
    public:
        Component();
        virtual ~Component();

        virtual void Tick(float deltaSeconds) = 0;
    };
}

#endif /* _LUCUS_ENGINE_COMPONENT_H */
