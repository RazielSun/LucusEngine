//
//  LucusViewCamera.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 30/12/2020.
//

#ifndef _LUCUS_ENGINE_VIEW_CAMERA_H
#define _LUCUS_ENGINE_VIEW_CAMERA_H

#include "LucusObject.h"
#include "LucusICamera.h"

namespace LucusEngine
{
    class ViewCamera : public Object, public ICamera
    {
    public:
        ViewCamera() noexcept;

        virtual void UpdateProjMatrix(const Viewport& viewport) override;
        
        virtual const FMatrix4x4& GetProjMatrix() const override;
        virtual const FMatrix4x4& GetViewMatrix() const override;

    protected:
        FMatrix4x4 mModelMtx;
    };
}

#endif /* _LUCUS_ENGINE_VIEW_CAMERA_H */
