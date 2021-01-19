//
//  lua_bind.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 31/12/2020.
//

#include "lua_bind.h"
#include "LucusLuaState.h"

#include "wrap_Core.h"

#include "wrap_World.h"
#include "wrap_Actor.h"
#include "wrap_Components.h"

using namespace LucusEngine;

namespace LucusEngine
{
    void BindLua(LuaState* state)
    {
        InitializeCore(state);
        
        InitializeWorld(state);
        InitializeActor(state);
        InitializeComponents(state);
    }
}

