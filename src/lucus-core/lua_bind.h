//
//  lua_bind.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 31/12/2020.
//

#ifndef _LUCUS_ENGINE_LUA_BIND_H
#define _LUCUS_ENGINE_LUA_BIND_H

namespace LucusEngine
{
    class LuaState;
}

void BindLua(LucusEngine::LuaState* state);

#endif /* _LUCUS_ENGINE_LUA_BIND_H */