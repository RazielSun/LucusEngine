//
//  SpringArmComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 12/04/2020.
//

#include "SpringArmComponent.h"

SpringArmComponent::SpringArmComponent() :
	mSpeed(1.0f),
	mRotation()
{
    //
}

SpringArmComponent::~SpringArmComponent()
{
    //
}

void SpringArmComponent::Tick(float deltaSeconds)
{
	float yaw = mRotation.yaw + mSpeed * deltaSeconds;
	if (yaw > 180.0f)
		yaw -= 360.0f;
	if (yaw <= -180.0f)
		yaw += 360.0f;
	mTransform.SetRotation(0.0f, 0.0f, yaw);
    // angle += 1.0f * deltaSeconds;
    // LucusEngine::FVector3 axis(0.0f, 1.0f, 0.0f);
    // mTransform.Rotate(axis, angle);
}

