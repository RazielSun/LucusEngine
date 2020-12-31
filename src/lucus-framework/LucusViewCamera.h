//
//  LucusViewCamera.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 30/12/2020.
//

#ifndef _LUCUS_ENGINE_VIEW_CAMERA_H
#define _LUCUS_ENGINE_VIEW_CAMERA_H

#include "LucusLuaObject.h"
#include "LucusICamera.h"

namespace LucusEngine
{
    class ViewCamera : public LuaObject, public ICamera
    {
    public:
        ViewCamera();
        virtual ~ViewCamera();
        
        DECL_LUA_OBJECT(ViewCamera)

        virtual void UpdateProjMatrix(const Viewport& viewport) override;
        
        virtual const FMatrix4x4& GetProjMatrix() const override;
        virtual const FMatrix4x4& GetViewMatrix() const override;

    protected:
        FMatrix4x4 mModelMtx;
    };
}

#endif /* _LUCUS_ENGINE_VIEW_CAMERA_H */
