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

namespace LucusEngine
{
    class ComponentProxy;

    class SceneComponent : public Component
    {
    public:
        SceneComponent();
        virtual ~SceneComponent();

    protected:
    	FVector3 mLocation;
        FQuaternion mRotation;
        FVector3 mScale;
    };
}

#endif /* _LUCUS_ENGINE_SCENE_COMPONENT_H */
