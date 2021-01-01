//
//  LucusWorld.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 29/02/2020.
//

#ifndef _LUCUS_ENGINE_WORLD_H
#define _LUCUS_ENGINE_WORLD_H

#include "LucusTypes.h"
#include "LucusLuaObject.h"
#include "LucusPtr.h"

namespace tinyxml2
{
    class XMLElement;
}

namespace LucusEngine
{
	class Scene;
	class Actor;
    class Component;

    using ActorPtr = Ptr<Actor>;

    typedef std::vector<ActorPtr> ActorArray;
    typedef ActorArray::iterator ActorIterator;

    class World : LuaObject
    {
    public:
        World();
        virtual ~World();
        
        DECL_LUA_OBJECT(World)

        void InitWorld();
        virtual void InitActors();
        void LoadActors(cc8* path);

        void Tick(float deltaSeconds);
        void LateTick();

        Scene* Scene;

        Actor* SpawnActor();
        Actor* SpawnActor(const tinyxml2::XMLElement*);
        // Actor* SpawnActor();
        
        void AddActor(Actor* actor);
        void RemoveActor(Actor* actor);
        
        virtual void BindLuaFunctions(lua_State* lua) override;
        
    protected:
        virtual Component* GetComponent(cc8* name);
        Component* CreateComponent(const tinyxml2::XMLElement*);
        
        bool CompareNames(cc8* name, cc8* component);

    protected:
    	ActorArray mActors;

    public:
        static int _addActor(lua_State* lua);
    };
}

#endif /* _LUCUS_ENGINE_WORLD_H */
