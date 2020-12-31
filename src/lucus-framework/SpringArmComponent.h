//
//  SpringArmComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 12/04/2020.
//

#ifndef _SPRING_ARM_COMPONENT_H
#define _SPRING_ARM_COMPONENT_H

#include "LucusSceneComponent.h"
#include "LucusRotator.h"

class SpringArmComponent : public LucusEngine::SceneComponent
{
public:
    SpringArmComponent();
    virtual ~SpringArmComponent();
    
    DECL_LUA_OBJECT(SpringArmComponent)

    virtual void Tick(float deltaSeconds) override;

protected:
    // float angle = 0.0f;
    float mSpeed;

    //f for Test
    LucusEngine::FRotator mRotation;
    
public:
    virtual void BindLuaFunctions(lua_State* lua) override;
};

#endif /* _SPRING_ARM_COMPONENT_H */

