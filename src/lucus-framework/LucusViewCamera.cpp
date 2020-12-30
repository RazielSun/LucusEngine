//
//  LucusViewCamera.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 30/12/2020.
//

#include "LucusViewCamera.h"
#include "LucusViewport.h"

using namespace LucusEngine;

ViewCamera::ViewCamera() :
    mModelMtx(FMatrix4x4::Identity)
{
}

ViewCamera::~ViewCamera()
{
    //
}

const FMatrix4x4& ViewCamera::GetProjMatrix() const
{
	return mProjMtx;
}

const FMatrix4x4& ViewCamera::GetViewMatrix() const
{
	return mModelMtx;
}

void ViewCamera::UpdateProjMatrix(const Viewport& viewport)
{
    mProjMtx = FMatrix4x4::RightHandProjectionMatrix(viewport.GetAspectRatio(), mNearZ, mFarZ, mFOV);
}
