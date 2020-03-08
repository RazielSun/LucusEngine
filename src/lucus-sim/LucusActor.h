//
//  LucusActor.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#ifndef _LUCUS_ENGINE_ACTOR_H
#define _LUCUS_ENGINE_ACTOR_H

#include "LucusTypes.h"
#include "LucusComponent.h"

namespace LucusEngine
{
    class World;

    class Actor
    {
    public:
        Actor();
        Actor(World* world);
        virtual ~Actor();

        virtual void Tick(float deltaTime);
        
        void SetRootComponent(Component* component);
        
        template <class T>
        void SetRootComponent(T* component) {
            SetRootComponent(dynamic_cast<Component*>(component));
        }
        
        Component* GetRootComponent();

    protected:
    	Component* RootComponent;
        
        World* mWorld;
    };
}

#endif /* _LUCUS_ENGINE_ACTOR_H */
