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

namespace tinyxml2
{
    class XMLElement;
}

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

        void InitWorld();
        virtual void InitActors();
        void LoadActors(cc8* path);

        void Tick(float deltaSeconds);

        Scene* Scene;

        Actor* SpawnActor();
        Actor* SpawnActor(const tinyxml2::XMLElement*);
        // Actor* SpawnActor();
        
        
    protected:
        virtual Component* GetComponent(cc8* name);
        Component* CreateComponent(const tinyxml2::XMLElement*);
        
        bool CompareNames(cc8* name, cc8* component);

    protected:
    	ActorArray mActors;
    };
}

#endif /* _LUCUS_ENGINE_WORLD_H */
