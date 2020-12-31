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

#include <iostream>

using namespace LucusEngine;

Actor::Actor() : mWorld(nullptr)
{
    //
}

Actor::~Actor()
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

void Actor::SetWorld(World* world)
{
    mWorld = world;
    // Do some stuff
}

template <class T>
void Actor::SetRootComponent(T* component)
{
    mRootComponent = Ptr<SceneComponent>(component);
    AddComponentToScene(mRootComponent.Get());
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

void Actor::BindLuaFunctions(lua_State* lua)
{
    const luaL_Reg reg_table[] = {
        { "SetRootComponent", _setRootComponent },
        { 0, 0 }
    };
    luaL_setfuncs(lua, reg_table, 0);
    lua_pushvalue(lua, -1);
}

int Actor::_setRootComponent(lua_State* lua)
{
    std::cout << "[C++] Actor SetRootComponent called.\n";
    return 0;
}
