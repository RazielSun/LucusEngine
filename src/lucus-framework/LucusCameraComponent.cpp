//
//  LucusCameraComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 6/03/2020.
//

#include "LucusCameraComponent.h"
#include "LucusViewport.h"

using namespace LucusEngine;

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
    //
}

const FMatrix4x4& CameraComponent::GetProjMatrix() const
{
	return mProjMtx;
}

const FMatrix4x4& CameraComponent::GetViewMatrix() const
{
	return GetModelMatrix();
}

void CameraComponent::UpdateProjMatrix(const Viewport& viewport)
{
    mProjMtx = FMatrix4x4::RightHandProjectionMatrix(viewport.GetAspectRatio(), mNearZ, mFarZ, mFOV);
}

void CameraComponent::BindLuaFunctions(lua_State* lua)
{
    SceneComponent::BindLuaFunctions(lua);
}
