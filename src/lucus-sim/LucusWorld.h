//
//  LucusWorld.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 29/02/2020.
//

#ifndef _LUCUS_ENGINE_WORLD_H
#define _LUCUS_ENGINE_WORLD_H

#include "LucusTypes.h"

#include <vector>

namespace LucusEngine
{
	class Scene;
	class Actor;
    class Component;

    typedef std::vector<Actor*> ActorArray;
    typedef ActorArray::iterator ActorIterator;

    class World
    {
    public:
        World();
        virtual ~World();

        virtual void InitWorld();

        void Tick(float deltaSeconds);

        Scene* Scene;

        Actor* SpawnActor();
        // Actor* SpawnActor();
        virtual Component* CreateComponent(сс8* name);

    protected:
    	ActorArray mActors;
    };
}

#endif /* _LUCUS_ENGINE_WORLD_H */
