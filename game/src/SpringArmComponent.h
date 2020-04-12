//
//  SpringArmComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 12/04/2020.
//

#ifndef _SPRING_ARM_COMPONENT_H
#define _SPRING_ARM_COMPONENT_H

#include "LucusSceneComponent.h"

class SpringArmComponent : public LucusEngine::SceneComponent
{
public:
    SpringArmComponent();
    virtual ~SpringArmComponent();

    virtual void Tick(float deltaSeconds) override;

protected:
    float angle = 0.0f;
};

#endif /* _SPRING_ARM_COMPONENT_H */

