//
//  LucusLuaStack.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 1/01/2021.
//

#ifndef _LUCUS_ENGINE_LUASTACK_H
#define _LUCUS_ENGINE_LUASTACK_H

#include "LucusTypes.h"
#include "LucusLuaState.h"
#include <iostream>
#include <string.h>

namespace LucusEngine
{
    class LuaStack
    {
    public:
        explicit LuaStack(lua_State* lua);
        ~LuaStack();

        u32 GetTop();
        bool IsType(int idx, int type);

        template <class T>
        T* GetLuaObject(int idx);

        void Push(cc8* str);
        void Push(const std::string& str);

        template <class T>
        T GetValue(int idx, T def);

    private:
        lua_State* mLua;
    };

    template <class T>
    T* LuaStack::GetLuaObject(int idx)
    {
        if (GetTop() < idx) return nullptr;
        if (IsType(idx, LUA_TTABLE))
        {
            if (lua_getmetatable(mLua, idx))
            {
                lua_pushstring(mLua, "__object");
                lua_gettable(mLua, -2);
                
                if (IsType(-1, LUA_TLIGHTUSERDATA))
                {
                    T* ptr = static_cast<T*>(lua_touserdata(mLua, -1));
                    lua_pop(mLua, 2);
                    return ptr;
                }
                lua_pop(mLua, 2);
            }
        }
        return nullptr;
    }

    template <> cc8* LuaStack::GetValue(int idx, cc8* def);
    template <> float LuaStack::GetValue(int idx, float def);
}

#endif /* _LUCUS_ENGINE_LUASTACK_H */
