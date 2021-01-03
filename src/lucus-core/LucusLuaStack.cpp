//
//  LucusLuaStack.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 1/01/2021.
//

#include "LucusLuaStack.h"
#include <string.h>

using namespace LucusEngine;


LuaStack::LuaStack(lua_State* lua) : mLua(lua)
{
    //
}

LuaStack::~LuaStack()
{
    //
}

int LuaStack::GetTop()
{
    return lua_gettop(mLua);
}

bool LuaStack::IsType(int idx, int type)
{
    return (lua_type(mLua, idx) == type);
}

void LuaStack::Push(cc8* str)
{
    lua_pushstring(mLua, str);
}

void LuaStack::Push(const std::string& str)
{
    lua_pushstring(mLua, str.c_str());
}

template <>
cc8* LuaStack::GetValue(int idx, cc8* def)
{
    if (IsType(idx, LUA_TSTRING))
    {
        return static_cast<cc8*>(lua_tostring(mLua, idx));
    }
    return def;
}

template <>
float LuaStack::GetValue(int idx, float def)
{
    if (IsType(idx, LUA_TNUMBER))
    {
        return static_cast<float>(lua_tonumber(mLua, idx));
    }
    return def;
}
