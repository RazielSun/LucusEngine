//
//  LucusLuaFactory.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 29/12/2020.
//

#ifndef _LUCUS_ENGINE_LUA_FACTORY_H
#define _LUCUS_ENGINE_LUA_FACTORY_H

#include "LucusLuaState.h"
#include "LucusLuaStack.h"
#include <iostream>
#include <sstream>
#include <string.h>

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
        
        lua_newtable(L);
        lua_newtable(L);
        
        lua_pushcfunction(L, LuaFactory<T>::_ctor);
        lua_setfield(L, -2, "__call");
        
        lua_setmetatable(L, -2);
        
        T temp;
        lua_setglobal(L, temp.GetTypeName());
    }

    template <class T>
    void LuaFactory<T>::RegisterGlobal(LuaState* state, T* object)
    {
        lua_State* L = state->GetRawLua();
        lua_newtable(L);
        lua_newtable(L);
        lua_pushstring(L, "__object");
        lua_pushlightuserdata(L, object);
        lua_settable(L, -3);
        
        lua_setmetatable(L, -2);
        
        object->BindLuaFunctions(L);
        
        lua_setglobal(L, object->GetTypeName());
    }

    template <class T>
    int LuaFactory<T>::_ctor(lua_State* L)
    {
    //        std::cout << "[C++] call ctor " << typeid(T).name() << std::endl;
        T* object = new T();
        lua_newtable(L);
        lua_newtable(L);
        lua_pushstring(L, "__object");
        lua_pushlightuserdata(L, object);
        lua_settable(L, -3);
        lua_pushcfunction(L, LuaFactory<T>::_gc);
        lua_setfield(L, -2, "__gc");
        lua_pushcfunction(L, LuaFactory<T>::_tostring);
        lua_setfield(L, -2, "__tostring");
        
        lua_setmetatable(L, -2);
        
        object->AddRef();
        object->BindLuaFunctions(L);

        return 1;
    }

    template <class T>
    int LuaFactory<T>::_tostring(lua_State* L)
    {
        LuaStack stack(L);
        T* ptr = stack.GetLuaObject<T>(1);
        if (ptr != nullptr)
        {
            std::stringstream s;
            s << "<"<< ptr->GetTypeName() << "(" << ptr << ")>";
            stack.Push(s.str());
            return 1;
        }
        stack.Push("<Wrong object>");
        return 1;
    }

    template <class T>
    int LuaFactory<T>::_gc(lua_State* L)
    {
        LuaStack stack(L);
        T* ptr = stack.GetLuaObject<T>(1);
        if (ptr != nullptr)
        {
            ptr->ReleaseRef();
        }
        return 0;
    }
}

#endif /* _LUCUS_ENGINE_LUA_FACTORY_H */