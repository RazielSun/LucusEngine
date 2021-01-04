//
//  lua_bind.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 31/12/2020.
//

#include "lua_bind.h"
#include "LucusLuaState.h"
#include "LucusLuaFactory.h"

#include "LucusActor.h"
#include "LucusViewCamera.h"


#include "LucusSceneComponent.h"
#include "LucusCameraComponent.h"
#include "LucusMeshComponent.h"

#include "SpringArmComponent.h"
#include "RotatedMeshComponent.h"

using namespace LucusEngine;

void BindLua(LuaState* state)
{
    LuaFactory<Actor>::RegisterClass(state);
    LuaFactory<ViewCamera>::RegisterClass(state);

    LuaFactory<SceneComponent>::RegisterClass(state);
    LuaFactory<CameraComponent>::RegisterClass(state);
    LuaFactory<MeshComponent>::RegisterClass(state);

    LuaFactory<SpringArmComponent>::RegisterClass(state);
    LuaFactory<RotatedMeshComponent>::RegisterClass(state);
}