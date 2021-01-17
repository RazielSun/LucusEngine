//
//  LucusLuaState.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 27/12/2020.
//

#ifndef _LUCUS_ENGINE_LUASTATE_H
#define _LUCUS_ENGINE_LUASTATE_H

#include "LucusTypes.h"
#include "LucusLuaStack.h"
#include "LucusLuaReference.h"

#include "lua_module.h"

namespace LucusEngine
{
    class LuaState
    {
    public:
        LuaState();
        ~LuaState();
        
        void Init();
        void Tick(float deltaSeconds);
        
        void RunScript(cc8* path);

        lua_State* GetRawLua() const { return mRawLua; }
        
    private:
        lua_State* mRawLua;
        LuaStack mStack;
        LuaReference mUpdateRef;
    };
}

#endif /* _LUCUS_ENGINE_LUASTATE_H */
