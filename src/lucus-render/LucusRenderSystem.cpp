
#include "LucusRenderSystem.h"
#include "LucusWorld.h"
#include "LucusScene.h"

using namespace LucusEngine;

RenderSystem::RenderSystem()
{
	//
}

RenderSystem::~RenderSystem()
{
	//
}

void RenderSystem::AllocateScene(World* world)
{
	if (world)
	{
		Scene* scene = new Scene();

		world->Scene = scene;

		mScene = scene;
	}
}