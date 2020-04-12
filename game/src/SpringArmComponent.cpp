//
//  SpringArmComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 12/04/2020.
//

#include "SpringArmComponent.h"

SpringArmComponent::SpringArmComponent()
{
    //
}

SpringArmComponent::~SpringArmComponent()
{
    //
}

void SpringArmComponent::Tick(float deltaSeconds)
{
    angle += 1.0f * deltaSeconds;
    LucusEngine::FVector3 axis(0.0f, 1.0f, 0.0f);
    mTransform.Rotate(axis, angle);
}

