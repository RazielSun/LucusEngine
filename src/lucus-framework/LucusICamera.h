//
//  LucusICamera.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 29/12/2020.
//

#ifndef _LUCUS_ENGINE_I_CAMERA_H
#define _LUCUS_ENGINE_I_CAMERA_H

#include "LucusMatrix.h"

namespace LucusEngine
{
    class Viewport;

    class ICamera
    {
    public:
        ICamera();

        virtual const FMatrix4x4& GetProjMatrix() const = 0;
        virtual const FMatrix4x4& GetViewMatrix() const = 0;

        virtual void UpdateProjMatrix(const Viewport& viewport) = 0;

    protected:
        FMatrix4x4 mProjMtx;

        float mFOV;
        float mNearZ;
        float mFarZ;
    };
}

#endif /* _LUCUS_ENGINE_I_CAMERA_H */
