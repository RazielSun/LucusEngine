//
//  LucusLuaState.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 27/12/2020.
//

#include "LucusLuaState.h"
#include "LucusFileSystem.h"
#include "LucusCore.h"

#include <iostream>
#include <string.h>

using namespace LucusEngine;

LuaState::LuaState() : _rawLua(luaL_newstate())
{
    luaL_openlibs(_rawLua);
}

LuaState::~LuaState()
{
    lua_close(_rawLua);
}

void LuaState::Do()
{
    int r = luaL_dofile(_rawLua, Core::GetFileSystem()->GetAssetPath("Assets/Scripts/main.lua").c_str());
    if (r != LUA_OK)
    {
        const char* msg = lua_tostring(_rawLua, -1);
        std::cout << "[C++] Lua error! " << msg << std::endl;
    }
}

