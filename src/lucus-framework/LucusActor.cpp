//
//  LucusActor.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#include "LucusActor.h"
#include "LucusWorld.h"
#include "LucusScene.h"
#include "LucusSceneComponent.h"
#include "LucusLuaStack.h"

#include <iostream>

using namespace LucusEngine;

Actor::Actor() noexcept : mWorld(nullptr) 
{
    //
}

Actor::~Actor() noexcept
{
    if (nullptr != mWorld)
    {
        mWorld->Scene->RemoveSceneComponent(mRootComponent.Get());
    }
}

void Actor::Tick(float deltaSeconds)
{
    if (mRootComponent)
    {
        mRootComponent->Tick(deltaSeconds);
    }
}

void Actor::LateTick()
{
    if (mRootComponent)
    {
        mRootComponent->LateTick();
    }
}

void Actor::SetWorld(World* world)
{
    mWorld = world;
    // Do some stuff
}

template <>
void Actor::SetRootComponent(SceneComponent* component)
{
    mRootComponent = Ptr<SceneComponent>(component);
}

template <class T>
void Actor::SetRootComponent(T* component)
{
    mRootComponent = Ptr<SceneComponent>(component);
    // AddComponentToScene(mRootComponent.Get());
}

SceneComponent* Actor::GetRootComponent()
{
    return mRootComponent.Get();
}

void Actor::AddComponentToScene(SceneComponent* component)
{
    if (nullptr != mWorld)
    {
        mWorld->Scene->AddSceneComponent(component);

        const ChildrenVector& children = component->GetChildren();
        for (auto& child : children)
        {
            AddComponentToScene(child.Get());
            // mWorld->Scene->AddSceneComponent(component);
        }
    }
}

// void Actor::BindLuaFunctions(lua_State* lua)
// {
//     LuaObject::BindLuaFunctions(lua);
    
//     const luaL_Reg reg_table[] = {
//         { "SetRootComponent", _setRootComponent },
//         { 0, 0 }
//     };
//     luaL_setfuncs(lua, reg_table, 0);
//     lua_pushvalue(lua, -1);
// }

// int Actor::_setRootComponent(lua_State* L)
// {
//     LuaStack stack(L);
//     Actor* actor = stack.GetLuaObject<Actor>(1);
//     SceneComponent* comp = stack.GetLuaObject<SceneComponent>(2);
//     if (actor != nullptr && comp != nullptr)
//     {
//         std::cout << "[C++] Actor SetRootComponent called.\n";
//         actor->SetRootComponent(comp);
//     }
//     return 0;
// }
