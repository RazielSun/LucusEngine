
#include "wrap_World.h"
#include "LucusLuaState.h"
#include "LucusLuaStack.h"
#include "LucusLuaFactory.h"

#include "LucusWorld.h"

using namespace LucusEngine;

#define LUCUS_LUA_WORLD_CLASS "world"

// void World::BindLuaFunctions(lua_State* lua)
// {
//     const luaL_Reg reg_table[] = {
//         { "AddActor", _addActor },
//         { 0, 0 }
//     };
//     luaL_setfuncs(lua, reg_table, 0);
//     lua_pushvalue(lua, -1);
// }

// int World::_addActor(lua_State* lua)
// {
//     LuaStack stack(lua);
//     World* world = stack.GetLuaObject<World>(1);
//     Actor* actor = stack.GetLuaObject<Actor>(2);
//     if (world != nullptr && actor != nullptr)
//     {
//         std::cout << "[C++] World _addActor called.\n";
//         std::cout << "[C++] World " << world << ", Actor " << actor << ".\n";
//         world->AddActor(actor);
//     }
//     return 0;
// }

// static const luaL_Reg World_methods = {
//     { "AddActor", _addActor },
//     { 0, 0 }
// }



// static const luaL_Reg World_meta = {
//     { "__gc", World_gc },
//     { 0, 0 }
// }

static int world_ctor(lua_State* L)
{
    // if (lua_gettop(L) != 1) return -1; // ?
    World* world = new World(); // TODO: Create from Core
    World** pptr = static_cast<World**>(lua_newuserdata(L, sizeof(World*)));
    *pptr = world;
    luaL_getmetatable(L, LUCUS_LUA_WORLD_CLASS);
    lua_setmetatable(L, -2);
    world->AddRef();
    return 1;
}

static int world_gc(lua_State* L)
{
    LuaStack stack(L);
    World* ptr = stack.GetLuaObject<World>(1);
    if (ptr != nullptr)
    {
        ptr->ReleaseRef();
    }
    return 0;
}

namespace LucusEngine
{
    void InitializeWorld(LuaState* state)
    {
        lua_State* L = state->GetRawLua();

        lua_getglobal(L, LUCUS_LUA_MAIN_MODULE);

        lua_pushcfunction(L, world_ctor);
        lua_setfield(L, -2, LUCUS_LUA_WORLD_CLASS);

        luaL_newmetatable(L, LUCUS_LUA_WORLD_CLASS);
        int meta_idx = lua_gettop(L);

        lua_pushcfunction(L, world_gc);
        lua_setfield(L, meta_idx, "__gc");

        lua_pop(L, 1); // meta
        lua_pop(L, 1); // global
    }
}

