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

    class World
    {
    public:
        World();
        ~World();

        void InitWorld();

        void Tick(float deltaSeconds);

        static World* CreateWorld();

        Scene* Scene;

        Actor* SpawnActor();

    protected:
    	std::vector<Actor*> mActors;
    };
}

#endif /* _LUCUS_ENGINE_WORLD_H */
