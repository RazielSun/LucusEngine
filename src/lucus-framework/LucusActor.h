//
//  LucusActor.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#ifndef _LUCUS_ENGINE_ACTOR_H
#define _LUCUS_ENGINE_ACTOR_H

#include "LucusTypes.h"
#include "LucusObject.h"
#include "LucusPtr.h"

namespace LucusEngine
{
    class World;
    class SceneComponent;

    using SceneComponentPtr = Ptr<SceneComponent>;

    class Actor : public Object
    {
    public:
        Actor() noexcept;
        virtual ~Actor() noexcept;

        virtual void Tick(float deltaSeconds);
        virtual void LateTick();

        void SetWorld(World* world);
        
        template <class T>
        void SetRootComponent(T* component);
        
        SceneComponent* GetRootComponent();

    protected:
        void AddComponentToScene(SceneComponent* component);

    protected:
    	SceneComponentPtr mRootComponent;
        
        World* mWorld;
        
    // public:
        // static int _setRootComponent(lua_State* L);
    };
}

#endif /* _LUCUS_ENGINE_ACTOR_H */
