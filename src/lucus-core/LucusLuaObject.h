//
//  LucusLuaObject.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 19/02/2021.
//

#ifndef _LUCUS_ENGINE_LUA_OBJECT_H
#define _LUCUS_ENGINE_LUA_OBJECT_H

#include "LucusTypes.h"
#include "LucusLuaStack.h"

namespace LucusEngine
{
    #define LUA_NAMESPACE(L, namespac) \
    lua_getglobal(L, namespac);

    #define ADD_CTOR(L, name, ctor) \
    lua_pushcfunction(L, ctor); \
    lua_setfield(L, -2, name);

    #define ADD_METATABLE(L, name, methods, meta) \
    luaL_newmetatable(L, name); \
    luaL_setfuncs(L, meta, 0); \
    lua_newtable(L); \
    luaL_setfuncs(L, methods, 0); \
    lua_setfield(L, -2, "__index"); \
    lua_pop(L, 1);

    #define ADD_INH_METATABLE(L, name, base_methods, methods, meta) \
    luaL_newmetatable(L, name); \
    luaL_setfuncs(L, meta, 0); \
    lua_newtable(L); \
    luaL_setfuncs(L, base_methods, 0); \
    luaL_setfuncs(L, methods, 0); \
    lua_setfield(L, -2, "__index"); \
    lua_pop(L, 1);

    #define SET_METATABLE(L, name) \
    luaL_getmetatable(L, name); \
    lua_setmetatable(L, -2);

    // #define LUA_OBJECT_GET_METHOD(L) \
    // lua_getmetatable(L, 1); \
    // lua_pushvalue(L, 2); \
    // lua_rawget(L, -2);

    template <class T>
    class LuaObject
    {
    public:
        // TODO: variadic?
        static T* constructor(lua_State* L);
        static int destructor(lua_State* L);
        static int index(lua_State* L);
    };

    template <class T>
    T* LuaObject<T>::constructor(lua_State* L)
    {
        T* ptr = new T();
        T** pptr = static_cast<T**>(lua_newuserdata(L, sizeof(T*)));
        *pptr = ptr;
        ptr->AddRef();
        return ptr;
    }

    template <class T>
    int LuaObject<T>::destructor(lua_State* L)
    {
        LuaStack stack(L);
        T* ptr = stack.GetLuaObject<T>(1);
        if (ptr != nullptr)
            ptr->ReleaseRef();
        return 0;
    }

    template <class T>
    int LuaObject<T>::index(lua_State* L)
    {
        lua_getmetatable(L, 1);
        lua_pushvalue(L, 2);
        lua_rawget(L, -2);
        if (lua_isnumber(L, -1))
        {
            // TODO: Called special getters by index
        }
        return 1;
    }
    
        
}

#endif /* _LUCUS_ENGINE_LUA_OBJECT_H */
