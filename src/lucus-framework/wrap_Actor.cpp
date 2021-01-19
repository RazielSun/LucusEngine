
#include "wrap_Actor.h"
#include "LucusLuaState.h"
#include "LucusLuaObject.h"

#include "LucusActor.h"
#include "LucusSceneComponent.h"

using namespace LucusEngine;

#define LUCUS_LUA_ACTOR_CLASS "Actor"

static int Actor_setRootComponent(lua_State* L)
{
    LuaStack stack(L);
    Actor* actor = stack.GetLuaObject<Actor>(1);
    SceneComponent* comp = stack.GetLuaObject<SceneComponent>(2);
    if (actor && comp)
    {
        // std::cout << "[C++] Actor SetRootComponent called.\n";
        actor->SetRootComponent(comp);
    }
    return 0;
}

static const luaL_Reg actor_methods[] = {
    { "SetRootComponent", Actor_setRootComponent },
    { 0, 0 }
};

static int actor_ctor(lua_State* L)
{
    // if (lua_gettop(L) != 1) return -1; // ?
    Actor* actor = LuaObject<Actor>::constructor(L);
    SET_METATABLE(L, LUCUS_LUA_ACTOR_CLASS)
    return 1;
}

static const luaL_Reg actor_meta[] = {
    { "__gc", &LuaObject<Actor>::destructor },
    { 0, 0 }
};

namespace LucusEngine
{
    void InitializeActor(LuaState* state)
    {
        lua_State* L = state->GetRawLua();

        LUA_NAMESPACE(L, LUCUS_LUA_MAIN_MODULE);
        ADD_CTOR(L, LUCUS_LUA_ACTOR_CLASS, actor_ctor);

        ADD_METATABLE(L, LUCUS_LUA_ACTOR_CLASS, actor_methods, actor_meta);

        // lua_pop(L, 1); // meta
        lua_pop(L, 1); // global
    }
}
