//
//  LucusMeshComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 5/03/2020.
//

#include "LucusMeshComponent.h"
#include "LucusMesh.h"

using namespace LucusEngine;

MeshComponent::MeshComponent() : mMesh(nullptr)
{
    //
}

MeshComponent::MeshComponent(cc8* name)
{
    mMesh = new LucusEngine::Mesh();
    mMesh->Load(name);
}

MeshComponent::~MeshComponent()
{
    if (nullptr != mMesh)
    {
        delete mMesh;
        mMesh = nullptr;
    }
}

Mesh* MeshComponent::GetMesh()
{
    return mMesh;
}
