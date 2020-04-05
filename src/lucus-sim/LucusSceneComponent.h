//
//  LucusSceneComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/04/2020.
//

#ifndef _LUCUS_ENGINE_SCENE_COMPONENT_H
#define _LUCUS_ENGINE_SCENE_COMPONENT_H

#include "LucusComponent.h"
#include "LucusVector.h"
#include "LucusQuaternion.h"
#include "LucusTransform.h"

namespace LucusEngine
{
    class SceneComponentProxy;

    class SceneComponent : public Component
    {
    public:
        SceneComponent();
        virtual ~SceneComponent();

        virtual void Tick(float deltaTime) override;
        
        SceneComponentProxy* Proxy;
        //        virtual ComponentProxy* CreateProxy();
        
        Transform& GetTransform() { return mTransform; }

    protected:
//    	FVector3 mLocation;
//        FQuaternion mRotation;
//        FVector3 mScale;
        
        Transform mTransform;
    };
}

#endif /* _LUCUS_ENGINE_SCENE_COMPONENT_H */
