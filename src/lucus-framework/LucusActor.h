//
//  LucusActor.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#ifndef _LUCUS_ENGINE_ACTOR_H
#define _LUCUS_ENGINE_ACTOR_H

#include "LucusTypes.h"
#include "LucusLuaObject.h"
#include "LucusPtr.h"

namespace LucusEngine
{
    class World;
    class SceneComponent;

    using SceneComponentPtr = Ptr<SceneComponent>;

    class Actor : public LuaObject
    {
    public:
        Actor();
        virtual ~Actor();
        
        DECL_LUA_OBJECT(Actor)

        virtual void Tick(float deltaSeconds);

        void SetWorld(World* world);
        
        template <class T>
        void SetRootComponent(T* component);
        
        SceneComponent* GetRootComponent();
        
        virtual void BindLuaFunctions(lua_State* lua) override;

    protected:
        void AddComponentToScene(SceneComponent* component);

    protected:
    	SceneComponentPtr mRootComponent;
        
        World* mWorld;
        
    public:
        static int _setRootComponent(lua_State* lua);
    };
}

#endif /* _LUCUS_ENGINE_ACTOR_H */
