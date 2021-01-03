//
//  LucusComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#ifndef _LUCUS_ENGINE_COMPONENT_H
#define _LUCUS_ENGINE_COMPONENT_H

#include "LucusTypes.h"
#include "LucusLuaObject.h"
#include "LucusPtr.h"

namespace LucusEngine
{
    class Component : public LuaObject
    {
    public:
        Component();
        virtual ~Component();

        virtual void Tick(float deltaSeconds) = 0;
        virtual void LateTick() = 0;
    };

    using ComponentPtr = Ptr<Component>;
}

#endif /* _LUCUS_ENGINE_COMPONENT_H */
