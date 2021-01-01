//
//  LucusMeshComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 5/03/2020.
//

#include "LucusMeshComponent.h"
#include "LucusCore.h"
#include "LucusResourceManager.h"
#include "LucusLuaStack.h"

#include "tinyxml2.h"

using namespace LucusEngine;

MeshComponent::MeshComponent() : mMesh(nullptr), mImage(nullptr)
{
    //
}

MeshComponent::MeshComponent(cc8* meshName) : mImage(nullptr)
{
    SetMesh(meshName);
}

MeshComponent::MeshComponent(cc8* meshName, cc8* imageName) : MeshComponent(meshName)
{
    SetImage(imageName);
}

MeshComponent::~MeshComponent()
{
// Use Smart Pointers for deleting resources
//    if (nullptr != mMesh)
//    {
//        delete mMesh;
//        mMesh = nullptr;
//    }
//
//    if (nullptr != mImage)
//    {
//        delete mImage;
//        mImage = nullptr;
//    }
}

void MeshComponent::Init(const tinyxml2::XMLElement* data)
{
    SceneComponent::Init(data);
    
    for(const tinyxml2::XMLElement* asset = data->FirstChildElement("Asset");
        asset;
        asset = asset->NextSiblingElement("Asset"))
    {
        cc8* AssetType = asset->Attribute("type");
        if (Compare(AssetType, "Mesh")) {
            SetMesh(asset->Attribute("path"));
        }
        else if (Compare(AssetType, "Image")) {
            SetImage(asset->Attribute("path"));
        }
    }
}

void MeshComponent::SetMesh(cc8* meshName)
{
//    if (nullptr != mMesh)
//    {
//        delete mMesh;
//        mMesh = nullptr;
//    }
    
    // mMesh = MeshPtr(new Mesh());
    // mMesh->Load(meshName);

    ResourceManager* mgr = Core::GetResourceMgr();
    if (nullptr != mgr)
    {
        mMesh = mgr->GetMesh(meshName);
    }
}

void MeshComponent::SetImage(cc8* imageName)
{
//    if (nullptr != mImage)
//    {
//        delete mImage;
//        mImage = nullptr;
//    }
    
    // mImage = ImagePtr(new Image());
    // mImage->Load(imageName);

    ResourceManager* mgr = Core::GetResourceMgr();
    if (nullptr != mgr)
    {
        mImage = mgr->GetImage(imageName);
    }
}

Mesh* MeshComponent::GetMesh()
{
    return mMesh.Get();
}

Image* MeshComponent::GetImage()
{
    return mImage.Get();
}

void MeshComponent::BindLuaFunctions(lua_State* lua)
{
    SceneComponent::BindLuaFunctions(lua);
    
    const luaL_Reg reg_table[] = {
        { "SetMesh", _setMesh },
        { "SetImage", _setImage },
        { 0, 0 }
    };
    luaL_setfuncs(lua, reg_table, 0);
    lua_pushvalue(lua, -1);
}
    
int MeshComponent::_setMesh(lua_State* L)
{
    LuaStack stack(L);
    MeshComponent* comp = stack.GetLuaObject<MeshComponent>(1);
    cc8* meshName = stack.GetValue<cc8*>(2, "");
    if (comp != nullptr)
    {
        comp->SetMesh(meshName);
    }
    return 0;
}

int MeshComponent::_setImage(lua_State* L)
{
    LuaStack stack(L);
    MeshComponent* comp = stack.GetLuaObject<MeshComponent>(1);
    cc8* imageName = stack.GetValue<cc8*>(2, "");
    if (comp != nullptr)
    {
        comp->SetImage(imageName);
    }
    return 0;
}
