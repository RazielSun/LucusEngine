//
//  LucusLuaReference.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 17/01/2021.
//

#include "LucusLuaReference.h"

#include "lua_module.h"

using namespace LucusEngine;

LuaReference::LuaReference() : mRef(LUA_REFNIL), mLua(NULL)
{
}

LuaReference::LuaReference(lua_State* L)
{
    Ref(L);
}

LuaReference::~LuaReference() noexcept
{
    Unref();
}

void LuaReference::Ref(lua_State* L)
{
    Unref();
    mLua = L;
    if (mLua)
    {
        mRef = luaL_ref(mLua, LUA_REGISTRYINDEX);
    }
}
void LuaReference::Unref()
{
    if (mLua && IsValid())
    {
        luaL_unref(mLua, LUA_REGISTRYINDEX, mRef);
        mRef = LUA_REFNIL;
        mLua = NULL;
    }
}

void LuaReference::Push() const
{
    if (mLua)
    {
        if (mRef != LUA_REFNIL)
        {
            lua_rawgeti(mLua, LUA_REGISTRYINDEX, mRef);
        }
        else
        {
            lua_pushnil(mLua);
        }
    }
}

bool LuaReference::IsValid() const
{
    return mRef != LUA_REFNIL;
}
