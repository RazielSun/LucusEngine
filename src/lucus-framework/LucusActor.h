//
//  LucusActor.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#ifndef _LUCUS_ENGINE_ACTOR_H
#define _LUCUS_ENGINE_ACTOR_H

#include "LucusTypes.h"
#include "LucusSceneComponent.h"

namespace LucusEngine
{
    class World;
//    class SceneComponent;

    class Actor
    {
    public:
        Actor();
        Actor(World* world);
        virtual ~Actor();

        virtual void Tick(float deltaSeconds);
        
        void SetRootComponent(SceneComponent* component);
        
        template <class T>
        void SetRootComponent(T* component);
        
        SceneComponent* GetRootComponent();

    protected:
        void AddComponentToScene(SceneComponent* component);

    protected:
    	SceneComponent* RootComponent;
        
        World* mWorld;
    };
    
    template <class T>
    void Actor::SetRootComponent(T* component) {
        SetRootComponent(dynamic_cast<SceneComponent*>(component));
    }
}

#endif /* _LUCUS_ENGINE_ACTOR_H */
