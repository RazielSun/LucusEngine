//
//  LucusActor.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#ifndef _LUCUS_ENGINE_ACTOR_H
#define _LUCUS_ENGINE_ACTOR_H

#include "LucusTypes.h"

namespace LucusEngine
{
	class Component;

    class Actor
    {
    public:
        Actor();
        virtual ~Actor();

        virtual void Update(float deltaTime);

    protected:
    	Component* RootComponent;
    };
}

#endif /* _LUCUS_ENGINE_ACTOR_H */
