//
//  LucusLuaState.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 27/12/2020.
//

#ifndef _LUCUS_ENGINE_LUASTATE_H
#define _LUCUS_ENGINE_LUASTATE_H

#include "LucusTypes.h"
#include "lua.hpp"

namespace LucusEngine
{
    class LuaState
    {
    public:
        LuaState();
        ~LuaState();
        
        void Do();

        lua_State* GetRawLua() const { return _rawLua; }
    private:
        lua_State* _rawLua;
    };
}

#endif /* _LUCUS_ENGINE_LUASTATE_H */
