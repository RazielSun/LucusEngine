//
//  LucusActor.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#include "LucusActor.h"
#include "LucusWorld.h"
#include "LucusScene.h"
#include "LucusComponent.h"

using namespace LucusEngine;

Actor::Actor() : RootComponent(nullptr)
{
    //
}

Actor::Actor(World* world) : mWorld(world)
{
    //
}

Actor::~Actor()
{
    if (nullptr != mWorld)
    {
        mWorld->Scene->RemoveComponent(RootComponent);
    }
}

void Actor::Tick(float deltaTime)
{
    //
}

void Actor::SetRootComponent(Component* component)
{
    RootComponent = component;
    if (nullptr != mWorld)
    {
        mWorld->Scene->AddComponent(RootComponent);
    }
}

Component* Actor::GetRootComponent()
{
    return RootComponent;
}
