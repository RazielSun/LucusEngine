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
    
    // Load World
    // Camera
    Actor* cameraActor = SpawnActor();
    CameraComponent* cameraCom = new CameraComponent();
    cameraActor->SetRootComponent(cameraCom);
    
    // Actors
    Actor* cube1Actor = SpawnActor();
    MeshComponent* mesh1Com = new MeshComponent("Assets/meshes/cube.fbx");
    mesh1Com->GetTransform().AddLocation(0, 0, -2);
    cube1Actor->SetRootComponent(mesh1Com);
    
    Actor* cube2Actor = SpawnActor();
    MeshComponent* mesh2Com = new MeshComponent("Assets/meshes/cube.fbx");
    mesh2Com->GetTransform().AddLocation(1, 0, -2);
    cube2Actor->SetRootComponent(mesh2Com);
    
    Actor* cube3Actor = SpawnActor();
    MeshComponent* mesh3Com = new MeshComponent("Assets/meshes/cube.fbx");
    mesh3Com->GetTransform().AddLocation(-1, 0, -2);
    cube3Actor->SetRootComponent(mesh3Com);
    
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
