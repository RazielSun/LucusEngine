//
//  LucusLuaFactory.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 29/12/2020.
//

#ifndef _LUCUS_ENGINE_LUA_FACTORY_H
#define _LUCUS_ENGINE_LUA_FACTORY_H

#include "LucusLuaState.h"

namespace LucusEngine
{
    template <class T>
    class LuaFactory
    {
    public:
        static void RegisterClass(LuaState* state);
        static void RegisterGlobal(LuaState* state, T* object);
    private:
        static int _ctor(lua_State* L);
        static int _tostring(lua_State* L);
        static int _gc(lua_State* L);
    };

    template <class T>
    void LuaFactory<T>::RegisterClass(LuaState* state)
    {
        lua_State* L = state->GetRawLua();
        
        lua_pushcfunction(L, LuaFactory<T>::_ctor);
        lua_setglobal(L, T::className);
    }

    template <class T>
    void LuaFactory<T>::RegisterGlobal(LuaState* state, T* object)
    {
        lua_State* L = state->GetRawLua();
        lua_newtable(L);
        lua_pushstring(L, "__object");
        lua_pushlightuserdata(L, object);
        lua_settable(L, -3);
        
        object->BindLuaFunctions(L);
        
        lua_setglobal(L, T::className);
    }

    template <class T>
    int LuaFactory<T>::_ctor(lua_State* L)
    {
        T* object = new T();
        lua_newtable(L);
        lua_pushstring(L, "__object");
        lua_pushlightuserdata(L, object);
        lua_settable(L, -3);
        
        lua_newtable(L);
        lua_pushcfunction(L, LuaFactory<T>::_gc);
        lua_setfield(L, -2, "__gc");
        lua_pushcfunction(L, LuaFactory<T>::_tostring);
        lua_setfield(L, -2, "__tostring");
        
        lua_setmetatable(L, -2);
        
        object->BindLuaFunctions(L);

        return 1;
    }

    template <class T>
    int LuaFactory<T>::_tostring(lua_State* L)
    {
        return 0;
    }

    template <class T>
    int LuaFactory<T>::_gc(lua_State* L)
    {
        lua_pushstring(L, "__object");
        lua_gettable(L, -2);
        if (lua_isuserdata(L, -1))
        {
            T* ptr = static_cast<T*>(lua_touserdata(L, -1));
            if (ptr != nullptr)
            {
                delete ptr;
            }
        }
        return 0;
    }
}

#endif /* _LUCUS_ENGINE_LUA_FACTORY_H */
