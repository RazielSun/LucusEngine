//
//  LucusCameraComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 5/03/2020.
//

#ifndef _LUCUS_ENGINE_CAMERA_COMPONENT_H
#define _LUCUS_ENGINE_CAMERA_COMPONENT_H


#include "LucusSceneComponent.h"
#include "LucusICamera.h"

namespace LucusEngine
{
    class CameraComponent : public SceneComponent, public ICamera
    {
    public:
        CameraComponent();
        virtual ~CameraComponent();
        
        virtual const FMatrix4x4& GetProjMatrix() const override;
        virtual const FMatrix4x4& GetViewMatrix() const override;

        virtual void UpdateProjMatrix(const Viewport& viewport) override;
    };
}

#endif /* _LUCUS_ENGINE_CAMERA_COMPONENT_H */
