//
//  LucusScene.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#include "LucusScene.h"
#include "LucusWorld.h"
#include "LucusComponent.h"
#include "LucusMeshComponent.h"
#include "LucusCameraComponent.h"

using namespace LucusEngine;

Scene::Scene(World* world) :
	mWorld(world),
    CameraComp(nullptr)
{
    //
}

Scene::~Scene()
{
    mWorld = nullptr;
}

void Scene::AddComponent(Component* comp)
{
	if (nullptr != comp)
	{
		MeshComponent* meshComp = dynamic_cast<MeshComponent*>(comp);
		if (nullptr != meshComp)
		{
			MeshComps.push_back(meshComp);
            return;
		}

		if (CameraComp == nullptr)
		{
			CameraComp = dynamic_cast<CameraComponent*>(comp);
		}
	}
}

void Scene::RemoveComponent(Component* comp)
{
	if (nullptr != comp)
    {
        //
    }
}
