//
//  LucusSceneComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/04/2020.
//

#include "LucusSceneComponent.h"
#include "LucusSceneComponentProxy.h"

#include "tinyxml2.h"

using namespace LucusEngine;

SceneComponent::SceneComponent() :
    mTransform(),
    Proxy(nullptr),
    mParent(nullptr)
{
    //
}

SceneComponent::~SceneComponent()
{
    //
}

void SceneComponent::Init(const tinyxml2::XMLElement* data)
{
    // Super Init for Component
    
    const tinyxml2::XMLElement* locData = data->FirstChildElement("Location");
    if (locData)
    {
        float x, y, z;
        locData->QueryAttribute("x", &x);
        locData->QueryAttribute("y", &y);
        locData->QueryAttribute("z", &z);
        mTransform.SetLocation(x, y, z);
    }
}

void SceneComponent::Tick(float deltaSeconds)
{
	//
}

void SceneComponent::AttachTo(SceneComponent* parent)
{
	if (parent != nullptr)
	{
		parent->AddChild(this);
		mParent = parent;
	}
}

void SceneComponent::Detach()
{
	if (mParent)
	{
		mParent->RemoveChild(this);
		mParent.Reset();
	}
}

void SceneComponent::AddChild(SceneComponent* child)
{
	if (child != nullptr)
	{
		Ptr<SceneComponent> childPtr(child);
		mChildren.push_back(childPtr);
	}
}

void SceneComponent::RemoveChild(SceneComponent* child)
{
	// remove child
}

void SceneComponent::UpdateCachedModelMatrix()
{
	mTransform.UpdateMatrices();
	if (mParent)
	{
		mTransform.SetCachedWorldMatrix(mTransform.GetModelMatrix());
	}
	else
	{
		mTransform.SetCachedWorldMatrix(mTransform.GetModelMatrix() * mParent->GetModelMatrix());
	}
}

FMatrix4x4 SceneComponent::GetModelMatrix() const
{
	return mTransform.GetCachedWorldMatrix();
}
