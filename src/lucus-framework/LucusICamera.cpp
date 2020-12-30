//
//  LucusICamera.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 30/12/2020.
//

#include "LucusICamera.h"

using namespace LucusEngine;

ICamera::ICamera() :
    mProjMtx(FMatrix4x4::Identity),
    mFOV(65),
    mNearZ(0.1f),
    mFarZ(1000.0f)
{
    //
}
