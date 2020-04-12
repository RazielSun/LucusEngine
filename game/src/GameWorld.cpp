//
//  GameWorld.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 06/04/2020.
//

#include "GameWorld.h"
#include "LucusActor.h"
#include "LucusComponent.h"
#include "SpringArmComponent.h"
#include "RotatedMeshComponent.h"

GameWorld::GameWorld()
{
	//
}

GameWorld::~GameWorld()
{
	//
}

void GameWorld::InitActors()
{
    LoadActors("Assets/Levels/level0.xml");
}

LucusEngine::Component* GameWorld::GetComponent(cc8* name)
{
    LucusEngine::Component* component = nullptr;
    if (CompareNames(name, "RotatedMeshComponent")) {
        component = new RotatedMeshComponent();
    }
    else if (CompareNames(name, "SpringArmComponent")) {
        component = new SpringArmComponent();
    }
    if (nullptr == component)
    {
        component = LucusEngine::World::GetComponent(name);
    }
    return component;
}
