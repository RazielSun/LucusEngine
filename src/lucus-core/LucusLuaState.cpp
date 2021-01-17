//
//  LucusLuaState.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 27/12/2020.
//

#include "LucusLuaState.h"
#include "LucusFileSystem.h"
#include "LucusCore.h"

using namespace LucusEngine;

LuaState::LuaState() : mRawLua(luaL_newstate()), mStack(mRawLua)
{
    luaL_openlibs(mRawLua);
}

LuaState::~LuaState()
{
    lua_close(mRawLua);
}

void LuaState::Init()
{
    mStack.PushGlobalTable(LUCUS_LUA_MAIN_MODULE);
    mStack.PushValueByName(LUCUS_LUA_MAIN_INIT_METHOD);
    mStack.CallTop();
    mStack.Pop();

    mStack.PushValueByName(LUCUS_LUA_MAIN_UPDATE_METHOD);
    mStack.Copy(-1);
    mUpdateRef.Ref(mRawLua);
    mStack.Pop(2);
}

void LuaState::Tick(float deltaSeconds)
{
    if (mUpdateRef.IsValid())
    {
        mUpdateRef.Push();
        mStack.Push(deltaSeconds);
        mStack.Call(-2, 1);
    }
}

void LuaState::RunScript(cc8* path)
{
    int r = luaL_dofile(mRawLua, Core::GetFileSystem()->GetScriptPath(path).c_str());
    if (r != LUA_OK)
    {
        const char* msg = lua_tostring(mRawLua, -1);
        std::cout << "[C++] Lua error! " << msg << std::endl;
    }
}

