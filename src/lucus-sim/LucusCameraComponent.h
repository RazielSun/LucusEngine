//
//  LucusCameraComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 5/03/2020.
//

#ifndef _LUCUS_ENGINE_CAMERA_COMPONENT_H
#define _LUCUS_ENGINE_CAMERA_COMPONENT_H

#include "LucusTypes.h"
#include "LucusMath.h"
#include "LucusComponent.h"

namespace LucusEngine
{
    class Viewport;

    class CameraComponent : public Component
    {
    public:
        CameraComponent();
        virtual ~CameraComponent();

        void UpdateProjectionMatrix(const Viewport& viewport);
        
        const FMatrix4x4& GetProjMatrix() const { return mProj; }

    protected:
        FMatrix4x4 mProj;

        float mFOV;
        float mNearZ;
        float mFarZ;
    };
}

#endif /* _LUCUS_ENGINE_CAMERA_COMPONENT_H */
