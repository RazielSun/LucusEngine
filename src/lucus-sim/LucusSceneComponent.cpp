//
//  LucusSceneComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/04/2020.
//

#include "LucusSceneComponent.h"
#include "LucusSceneComponentProxy.h"

using namespace LucusEngine;

SceneComponent::SceneComponent() :
   mTransform(),
   Proxy(nullptr)
{
    //
}

SceneComponent::~SceneComponent()
{
    //
}

void SceneComponent::Tick(float deltaSeconds)
{
	//
}
