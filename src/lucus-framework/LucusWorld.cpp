//
//  LucusWorld.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 29/02/2020.
//

#include "LucusWorld.h"
#include "LucusCore.h"
#include "LucusResourceManager.h"
#include "LucusRenderSystem.h"
#include "LucusScene.h"
#include "LucusLuaStack.h"
#include "LucusActor.h"

#include <iostream>

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
}

void World::Tick(float deltaSeconds)
{
    for (ActorIterator it = mActors.begin(); it != mActors.end(); it++)
    {
        (*it)->Tick(deltaSeconds);
    }
}

void World::LateTick()
{
    for (ActorIterator it = mActors.begin(); it != mActors.end(); it++)
    {
        (*it)->LateTick();
    }
}

void World::AddActor(Actor* actor)
{
    if (actor != nullptr)
    {
        bool founded = false;
        ActorIterator it = mActors.begin();
        while (it != mActors.end())
        {
            if (it->Get() == actor)
            {
                founded = true;
                break;
            }
            it++;
        }
        if (!founded)
        {
            auto data = Ptr<Actor>(actor);
            mActors.push_back(data);
            if (Scene != nullptr)
            {
                Scene->AddSceneComponent(data->GetRootComponent());
            }
        }
    }
}

void World::RemoveActor(Actor* actor)
{
    //
}

void World::BindLuaFunctions(lua_State* lua)
{
    const luaL_Reg reg_table[] = {
        { "AddActor", _addActor },
        { 0, 0 }
    };
    luaL_setfuncs(lua, reg_table, 0);
    lua_pushvalue(lua, -1);
}

int World::_addActor(lua_State* lua)
{
    LuaStack stack(lua);
    World* world = stack.GetLuaObject<World>(1);
    Actor* actor = stack.GetLuaObject<Actor>(2);
    if (world != nullptr && actor != nullptr)
    {
        std::cout << "[C++] World _addActor called.\n";
        std::cout << "[C++] World " << world << ", Actor " << actor << ".\n";
        world->AddActor(actor);
    }
    return 0;
}
