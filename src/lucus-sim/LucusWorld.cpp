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

World::World() :
	mFrameCounter(0),
	mElapsedSeconds(0.0)
{
    mLastTime = mClock.now();
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
    meshCom->GetTransform().AddLocation(0, 0, -4);
    cubeActor->SetRootComponent(meshCom);
    
    if (system)
    {
        system->CreateBuffers();
    }
}

void World::Tick()
{
	mFrameCounter++;

	auto currentTime = mClock.now();
	auto deltaTime = currentTime - mLastTime;
	mLastTime = currentTime;

	mElapsedSeconds += deltaTime.count() * 1e-9;
	float dt = deltaTime.count() * 1e-9;

	if (mElapsedSeconds > 1.0)
	{
        // char buffer[500];
        // auto fps = frameCounter / elapsedSeconds;
        // sprintf_s(buffer, 500, "FPS: %f\n", fps);
        // OutputDebugString(buffer);
		mFrameCounter = 0;
		mElapsedSeconds = 0.0;
	}

	// Update Actors And Components

	//     frameCounter++;
//     auto t1 = clock.now();
//     auto deltaTime = t1 - t0;
//     t0 = t1;

// 	elapsedSeconds += deltaTime.count() * 1e-9;
//     if (elapsedSeconds > 1.0)
//     {

//         frameCounter = 0;
//         elapsedSeconds = 0.0;
//     }

// 	// Don't try render in first frame
// 	// if (m_frameCount == 0)
// 	// {
// 	// 	return;
// 	// }

// 	if (frameCounter != 0)
// 		Render();
// }
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
