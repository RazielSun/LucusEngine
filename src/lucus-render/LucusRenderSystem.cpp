
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
		Scene* scene = new Scene(world);

		world->Scene = scene;

		mScene = scene;
	}
}

void RenderSystem::ChangeViewportSize(u32 width, u32 height)
{
    for (auto it = mWindows.begin(); it != mWindows.end(); it++)
    {
        (*it)->GetViewport().ChangeSize(width, height);
    }
}
