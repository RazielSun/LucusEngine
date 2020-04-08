//
//  RotatedMeshComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 06/04/2020.
//

#include "RotatedMeshComponent.h"

RotatedMeshComponent::RotatedMeshComponent()
{
	//
}

RotatedMeshComponent::~RotatedMeshComponent()
{
	//
}

void RotatedMeshComponent::Tick(float deltaSeconds)
{
    angle += 1.0f * deltaSeconds;
    LucusEngine::FVector3 axis(0.0f, 1.0f, 0.0f);
    mTransform.Rotate(axis, angle);
}
