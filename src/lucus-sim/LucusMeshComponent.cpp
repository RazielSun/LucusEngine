//
//  LucusMeshComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 5/03/2020.
//

#include "LucusMeshComponent.h"
#include "LucusMesh.h"
#include "LucusImage.h"

using namespace LucusEngine;

MeshComponent::MeshComponent() : mMesh(nullptr), mImage(nullptr)
{
    //
}

MeshComponent::MeshComponent(cc8* meshName) : mImage(nullptr)
{
    mMesh = new Mesh();
    mMesh->Load(meshName);
}

MeshComponent::MeshComponent(cc8* meshName, cc8* imageName) : MeshComponent(meshName)
{
    mImage = new Image();
    mImage->Load(imageName);
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

void MeshComponent::Tick(float deltaTime)
{
    angle += 0.01f;
    FVector3 axis(0.0f, 1.0f, 0.0f);
    mTransform.UpdateRotateMatrix(axis, angle);
}

Mesh* MeshComponent::GetMesh()
{
    return mMesh;
}

Image* MeshComponent::GetImage()
{
    return mImage;
}
