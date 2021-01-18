
#include "wrap_Core.h"
#include "LucusLuaState.h"
#include "LucusLuaFactory.h"
#include "LucusLuaStack.h"

#include "LucusCore.h"
#include "LucusWorld.h"

using namespace LucusEngine;

#define LUCUS_LUA_CORE_MODULE "core"

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

// static int World_gc(lua_State* L)
// {
//     return 0;
// }

// static const luaL_Reg World_meta = {
//     { "__gc", World_gc },
//     { 0, 0 }
// }

static int core_index(lua_State* L)
{
    if (lua_gettop(L) != 2) return -1;
    LuaStack stack(L);
    Core* core = stack.GetLuaObject<Core>(1);
    auto property = stack.GetValue<cc8*>(2, "none");
    std::cout << "[C++] core_index[ " << property << " ]\n";
    return 0;
}

static int core_newindex(lua_State* L)
{
    if (lua_gettop(L) != 3) return -1;
    LuaStack stack(L);
    Core* core = stack.GetLuaObject<Core>(1);
    auto property = stack.GetValue<cc8*>(2, "none");
    World* world = stack.GetLuaObject<World>(3);
    std::cout << "[C++] core_newindex[ " << property << " ] = " << world << std::endl;
    return 0;
}

static int core_gc(lua_State* L)
{
    return 0;
}

namespace LucusEngine
{
    void InitializeCore(LuaState* state)
    {
        lua_State* L = state->GetRawLua();

        lua_getglobal(L, LUCUS_LUA_MAIN_MODULE);

        Core** pptr = static_cast<Core**>(lua_newuserdata(L, sizeof(Core*)));
        *pptr = Core::GetPtr();
        int core_idx = lua_gettop(L);

        lua_newtable(L);
        int meta_idx = lua_gettop(L);

        lua_pushcfunction(L, core_gc);
        lua_setfield(L, meta_idx, "__gc");

        lua_pushcfunction(L, core_index);
        lua_setfield(L, meta_idx, "__index");

        lua_pushcfunction(L, core_newindex);
        lua_setfield(L, meta_idx, "__newindex");

        lua_setmetatable(L, core_idx);

        lua_setfield(L, -2, LUCUS_LUA_CORE_MODULE);
        lua_pop(L, 1);
    }
}
