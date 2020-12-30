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
#include "LucusActor.h"
#include "LucusComponent.h"

#include "LucusCameraComponent.h"
#include "LucusMeshComponent.h"

#include "tinyxml2.h"
#include <iostream>

using namespace LucusEngine;

const char World::className[] = "World";

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
    
//    this->InitActors();
//
//    if (system)
//    {
//        system->CreateBuffers();
//    }
}

void World::InitActors()
{
    //
}

void World::LoadActors(cc8* path)
{
    ResourceManager* mgr = Core::GetResourceMgr();
    if (nullptr != mgr)
    {
        tinyxml2::XMLDocument document;
        u32 status = mgr->LoadXMLFile(path, document);
        if (status == 0) // Success
        {
            const tinyxml2::XMLElement* worldData = document.FirstChildElement("World");
            for (const tinyxml2::XMLElement* actorData = worldData->FirstChildElement("Actor");
                 actorData;
                 actorData = actorData->NextSiblingElement("Actor"))
            {
                // Create Actor
                SpawnActor(actorData);
            }
        }
    }
}

void World::Tick(float deltaSeconds)
{
    for (ActorIterator it = mActors.begin(); it != mActors.end(); it++)
    {
        (*it)->Tick(deltaSeconds);
    }
}

// World* World::CreateWorld()
// {
// 	World* world = new World();
// 	world->InitWorld();
// 	return world;
// }

Actor* World::SpawnActor()
{
//    Actor* actor = new Actor(this);
//    mActors.push_back(actor);
//	return actor;
    return nullptr;
}

Actor* World::SpawnActor(const tinyxml2::XMLElement* data)
{
//    Actor* actor = new Actor(this);
//    
//    const tinyxml2::XMLElement* rootComData = data->FirstChildElement("Component");
//    LucusEngine::Component* com = CreateComponent(rootComData);
//    
//    LucusEngine::SceneComponent* rootSceneCom = dynamic_cast<LucusEngine::SceneComponent*>(com);
//    actor->SetRootComponent(rootSceneCom);
//    
////    std::cout << actorData->Name() << " " << rootComData->Attribute("type") << std::endl;
//    mActors.push_back(actor);
//    return actor;
    
    return nullptr;
}

Component* World::GetComponent(cc8* name)
{
    Component* component = nullptr;
    if (CompareNames(name, "SceneComponent")) {
        component = new SceneComponent();
    }
    else if (CompareNames(name, "MeshComponent")) {
        component = new MeshComponent();
    }
    else if (CompareNames(name, "CameraComponent")) {
        component = new CameraComponent();
    }
    return component;
}

Component* World::CreateComponent(const tinyxml2::XMLElement* data)
{
    Component* component = this->GetComponent(data->Attribute("type"));
    if (nullptr != component)
    {
        component->Init(data);

        SceneComponent* sceneCom = dynamic_cast<SceneComponent*>(component);

        for (const tinyxml2::XMLElement* comData = data->FirstChildElement("Component");
                 comData;
                 comData = comData->NextSiblingElement("Component"))
        {
            // Create Child Components
            Component* childComponent = CreateComponent(comData);

            SceneComponent* childSceneCom = dynamic_cast<SceneComponent*>(childComponent);

            if (childSceneCom != nullptr)
            {
                childSceneCom->AttachTo(sceneCom);
            }
        }
    }
    return component;
}

bool World::CompareNames(cc8* name, cc8* component)
{
    return strncmp(name, component, strlen(component)) == 0;
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
    std::cout << "[C++] World _addActor called.\n";
    return 0;
}
