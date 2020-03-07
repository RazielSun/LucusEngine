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
#include <chrono>

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

        void Tick();

        static World* CreateWorld();

        Scene* Scene;

        Actor* SpawnActor();

    protected:
    	std::vector<Actor*> mActors;

    	u32 mFrameCounter;
    	double mElapsedSeconds;
		std::chrono::high_resolution_clock mClock;
		std::chrono::time_point mLastTime;
    };
}

#endif /* _LUCUS_ENGINE_WORLD_H */
