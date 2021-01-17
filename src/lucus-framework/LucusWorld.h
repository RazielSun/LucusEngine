//
//  LucusWorld.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 29/02/2020.
//

#ifndef _LUCUS_ENGINE_WORLD_H
#define _LUCUS_ENGINE_WORLD_H

#include "LucusTypes.h"
#include "LucusPtr.h"

namespace LucusEngine
{
	class Scene;
	class Actor;
    class Component;

    using ActorPtr = Ptr<Actor>;

    typedef std::vector<ActorPtr> ActorArray;
    typedef ActorArray::iterator ActorIterator;

    class World
    {
    public:
        World() noexcept;
        virtual ~World() noexcept;

        void InitWorld();

        void Tick(float deltaSeconds);
        void LateTick();

        Scene* Scene;
        
        void AddActor(Actor* actor);
        void RemoveActor(Actor* actor);

    protected:
    	ActorArray mActors;
    };
}

#endif /* _LUCUS_ENGINE_WORLD_H */
