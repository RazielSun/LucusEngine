//
//  LucusCameraComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 6/03/2020.
//

#include "LucusCameraComponent.h"
#include "LucusViewport.h"

using namespace LucusEngine;

CameraComponent::CameraComponent() :
	mProj(),
	mFOV(60),
	mNearZ(0.1f),
	mFarZ(1000.0f)
{
    //
}

CameraComponent::~CameraComponent()
{
    //
}

void CameraComponent::UpdateProjectionMatrix(const Viewport* viewport)
{
    //
}