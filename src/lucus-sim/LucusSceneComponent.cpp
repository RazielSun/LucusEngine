//
//  LucusSceneComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/04/2020.
//

#include "LucusSceneComponent.h"
#include "LucusSceneComponentProxy.h"

#include "tinyxml2.h"

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

void SceneComponent::Init(const tinyxml2::XMLElement* data)
{
    // Super Init for Component
    
    const tinyxml2::XMLElement* locData = data->FirstChildElement("Location");
    if (locData)
    {
        float x, y, z;
        locData->QueryAttribute("x", &x);
        locData->QueryAttribute("y", &y);
        locData->QueryAttribute("z", &z);
        mTransform.SetLocation(x, y, z);
    }
}

void SceneComponent::Tick(float deltaSeconds)
{
	//
}
