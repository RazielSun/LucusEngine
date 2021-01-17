//
//  LucusLuaStack.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 1/01/2021.
//

#ifndef _LUCUS_ENGINE_LUASTACK_H
#define _LUCUS_ENGINE_LUASTACK_H

#include "LucusTypes.h"

#include "lua_module.h"

namespace LucusEngine
{
    class LuaStack
    {
    public:
        explicit LuaStack(lua_State* L) : mLua(L) {}

        int GetTop();
        bool IsType(int idx, int type);

        template <class T>
        T* GetLuaObject(int idx);
        
        void CallTop(int num = 0, int ret = 0);
        void Call(int idx, int num = 0, int ret = 0);
        
        void Push(float value);
        void Push(cc8* str);
        void Push(const std::string& str);

        void PushGlobalTable(cc8* str);
        void PushValueByName(cc8* str, int idx = -1);

        void Copy(int idx);

        void Pop(int n = 1);

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
    template <> u32 LuaStack::GetValue(int idx, u32 def);
}

#endif /* _LUCUS_ENGINE_LUASTACK_H */
