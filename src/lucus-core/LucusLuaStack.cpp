//
//  LucusLuaStack.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 1/01/2021.
//

#include "LucusLuaStack.h"

using namespace LucusEngine;

int LuaStack::GetTop()
{
    return lua_gettop(mLua);
}

bool LuaStack::IsType(int idx, int type)
{
    return (lua_type(mLua, idx) == type);
}

void LuaStack::CallTop(int num, int ret)
{
    Call(-1, num, ret);
}

void LuaStack::Call(int idx, int num, int ret)
{
    if (IsType(idx, LUA_TFUNCTION))
    {
        if (lua_pcall(mLua, num, ret, 0) != LUA_OK)
        {
            std::string errormsg = lua_tostring(mLua, -1);
            std::cerr << errormsg << std::endl;
        }
    }
}

void LuaStack::Push(float value)
{
    lua_pushnumber(mLua, value);
}

void LuaStack::Push(cc8* str)
{
    lua_pushstring(mLua, str);
}

void LuaStack::Push(const std::string& str)
{
    lua_pushstring(mLua, str.c_str());
}

void LuaStack::PushGlobalTable(cc8* str)
{
    lua_getglobal(mLua, str);
    if (IsType(-1, LUA_TNIL))
    {
        lua_newtable(mLua);
        Copy(-1);
        lua_setglobal(mLua, str);
    }
}

void LuaStack::PushValueByName(cc8* str, int idx)
{
    if (IsType(idx, LUA_TTABLE))
    {
        Copy(idx);
        Push(str);
        lua_gettable(mLua, -2);
    }
}

void LuaStack::Copy(int idx)
{
    lua_pushvalue(mLua, idx);
}

void LuaStack::Pop(int n)
{
    lua_pop(mLua, n);
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

template <>
u32 LuaStack::GetValue(int idx, u32 def)
{
    if (IsType(idx, LUA_TNUMBER))
    {
        return static_cast<u32>(lua_tonumber(mLua, idx));
    }
    return def;
}
