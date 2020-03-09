//
//  LucusWorld.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 29/02/2020.
//

#include "LucusWorld.h"
#include "LucusRenderSystem.h"
#include "LucusScene.h"
#include "LucusActor.h"
#include "LucusCameraComponent.h"
#include "LucusMeshComponent.h"
#include "LucusCore.h"

using namespace LucusEngine;

World::World()
{
}

World::~World()
{
	// deallocate from system?

    if (this->Scene)
    {
    	delete this->Scene;
    	this->Scene = nullptr;
    }
}

void World::InitWorld()
{
    // Allocate Scene
    RenderSystem* system = Core::GetRenderSystem();
    if (system)
    {
    	system->AllocateScene(this);
    }
    
    Actor* cameraActor = SpawnActor();
    CameraComponent* cameraCom = new CameraComponent();
    cameraActor->SetRootComponent(cameraCom);
    
    Actor* cubeActor = SpawnActor();
    MeshComponent* meshCom = new MeshComponent("Assets/meshes/cube.fbx");
    meshCom->GetTransform().AddLocation(0, 0, -2);
    cubeActor->SetRootComponent(meshCom);
    
    if (system)
    {
        system->CreateBuffers();
    }
}

void World::Tick(float deltaSeconds)
{
	//
}

World* World::CreateWorld()
{
	World* world = new World();
	world->InitWorld();
	return world;
}

Actor* World::SpawnActor()
{
    Actor* actor = new Actor(this);
    mActors.push_back(actor);
	return actor;
}
