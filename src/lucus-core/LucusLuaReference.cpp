//
//  LucusLuaReference.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 17/01/2021.
//

#include "LucusLuaReference.h"

#include "lua_module.h"

using namespace LucusEngine;

LuaReference::LuaReference() : mRef(LUA_NOREF), mLua(nullptr)
{
}

LuaReference::LuaReference(lua_State* L) : mLua(L),  mRef(luaL_ref(L, LUA_REGISTRYINDEX))
{
}

LuaReference::LuaReference(LuaReference&& other) noexcept
{
    mLua = other.mLua;
    mRef = other.mRef;
    other.mRef = LUA_NOREF;
}

LuaReference::~LuaReference() noexcept
{
    if (IsValid())
    {
        luaL_unref(mLua, LUA_REGISTRYINDEX, mRef);
        mRef = LUA_NOREF;
        mLua = nullptr;
    }
}

LuaReference& LuaReference::operator=(LuaReference&& other) noexcept
{
    std::swap(mLua, other.mLua);
    std::swap(mRef, other.mRef);
    return *this;
}

void LuaReference::Push() const
{
    if (mLua)
    {
        if (mRef != LUA_NOREF)
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
    return mLua != nullptr && mRef != LUA_NOREF;
}
