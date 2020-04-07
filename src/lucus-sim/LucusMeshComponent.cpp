//
//  LucusMeshComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 5/03/2020.
//

#include "LucusMeshComponent.h"
#include "LucusMesh.h"
#include "LucusImage.h"

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
    if (nullptr != mMesh)
    {
        delete mMesh;
        mMesh = nullptr;
    }
    
    if (nullptr != mImage)
    {
        delete mImage;
        mImage = nullptr;
    }
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
    if (nullptr != mMesh)
    {
        delete mMesh;
        mMesh = nullptr;
    }
    
    mMesh = new Mesh();
    mMesh->Load(meshName);
}

void MeshComponent::SetImage(cc8* imageName)
{
    if (nullptr != mImage)
    {
        delete mImage;
        mImage = nullptr;
    }
    
    mImage = new Image();
    mImage->Load(imageName);
}

Mesh* MeshComponent::GetMesh()
{
    return mMesh;
}

Image* MeshComponent::GetImage()
{
    return mImage;
}
