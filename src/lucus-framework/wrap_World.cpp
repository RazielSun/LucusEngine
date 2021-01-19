
#include "wrap_World.h"
#include "LucusLuaState.h"
#include "LucusLuaStack.h"
#include "LucusLuaObject.h"

#include "LucusWorld.h"
#include "LucusActor.h"

using namespace LucusEngine;

#define LUCUS_LUA_WORLD_CLASS "World"

int World_addActor(lua_State* L)
{
    LuaStack stack(L);
    World* world = stack.GetLuaObject<World>(1);
    Actor* actor = stack.GetLuaObject<Actor>(2);
    if (world && actor)
    {
        std::cout << "[C++] World _addActor called.\n";
        std::cout << "[C++] World " << world << ", Actor " << actor << ".\n";
        world->AddActor(actor);
    }
    return 0;
}

static const luaL_Reg world_methods[] = {
    { "AddActor", World_addActor },
    { 0, 0 }
};

static int world_ctor(lua_State* L)
{
    // if (lua_gettop(L) != 1) return -1; // ?
    // TODO: Create from Core like a module ?
    World* world = LuaObject<World>::constructor(L);
    SET_METATABLE(L, LUCUS_LUA_WORLD_CLASS)
    return 1;
}

// static int world_index(lua_State* L)
// {
//     LUA_OBJECT_GET_METHOD(L);
//     if (lua_isnumber(L, -1))
//     {
//         // TODO: ?
//     }
//     return 1;
// }

// static int world_gc(lua_State* L)
// {
//     LuaObject<World>::destructor(L);
//     return 0;
// }

static const luaL_Reg world_meta[] = {
    { "__index", &LuaObject<World>::index },
    { "__gc", &LuaObject<World>::destructor },
    { 0, 0 }
};

namespace LucusEngine
{
    void InitializeWorld(LuaState* state)
    {
        lua_State* L = state->GetRawLua();

        LUA_NAMESPACE(L, LUCUS_LUA_MAIN_MODULE);
        ADD_CTOR(L, LUCUS_LUA_WORLD_CLASS, world_ctor);

        ADD_METATABLE(L, LUCUS_LUA_WORLD_CLASS, world_methods, world_meta);

        // lua_pop(L, 1); // meta
        lua_pop(L, 1); // global
    }
}
