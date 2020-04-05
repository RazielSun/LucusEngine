//
//  LucusActor.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#include "LucusActor.h"
#include "LucusWorld.h"
#include "LucusScene.h"

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
        mWorld->Scene->RemoveSceneComponent(RootComponent);
    }
}

void Actor::Tick(float deltaSeconds)
{
    if (nullptr != RootComponent)
    {
        RootComponent->Tick(deltaSeconds);
    }
}

void Actor::SetRootComponent(SceneComponent* component)
{
    RootComponent = component;
    if (nullptr != mWorld)
    {
        mWorld->Scene->AddSceneComponent(RootComponent);
    }
}

SceneComponent* Actor::GetRootComponent()
{
    return RootComponent;
}
