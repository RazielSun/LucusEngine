
#include "wrap_Components.h"
#include "LucusLuaState.h"
#include "LucusLuaObject.h"

#include "LucusSceneComponent.h"
#include "LucusMeshComponent.h"
#include "LucusCameraComponent.h"
#include "SpringArmComponent.h"

using namespace LucusEngine;

#define LUCUS_LUA_SCENE_COMPONENT_CLASS "SceneComponent"
#define LUCUS_LUA_MESH_COMPONENT_CLASS "MeshComponent"
#define LUCUS_LUA_CAMERA_COMPONENT_CLASS "CameraComponent"
#define LUCUS_LUA_SPRING_ARM_COMPONENT_CLASS "SpringArmComponent"

static int SceneComponent_addChild(lua_State* L)
{
    LuaStack stack(L);
    SceneComponent* parent = stack.GetLuaObject<SceneComponent>(1);
    SceneComponent* child = stack.GetLuaObject<SceneComponent>(2);
    if (parent != nullptr && child != nullptr)
    {
        child->AttachTo(parent);
    }
    return 0;
}

static int SceneComponent_removeChild(lua_State* L)
{
    return 0;
}

static int SceneComponent_attachTo(lua_State* L)
{
    return 0;
}

static int SceneComponent_detach(lua_State* L)
{
    return 0;
}

static int SceneComponent_setLocation(lua_State* L)
{
    LuaStack stack(L);
    SceneComponent* comp = stack.GetLuaObject<SceneComponent>(1);
    float x = stack.GetValue<float>(2, 0.f);
    float y = stack.GetValue<float>(3, 0.f);
    float z = stack.GetValue<float>(4, 0.f);
    if (comp != nullptr)
    {
        comp->GetTransform().SetLocation(x, y, z);
    }
    return 0;
}

static int SceneComponent_setRotation(lua_State* L)
{
    LuaStack stack(L);
    SceneComponent* comp = stack.GetLuaObject<SceneComponent>(1);
    float roll = stack.GetValue<float>(2, 0.f);
    float pitch = stack.GetValue<float>(3, 0.f);
    float yaw = stack.GetValue<float>(4, 0.f);
    if (comp != nullptr)
    {
        comp->GetTransform().SetRotation(roll, pitch, yaw);
    }
    return 0;
}

static const luaL_Reg sceneComponent_methods[] = {
    { "AddChild", SceneComponent_addChild },
    { "RemoveChild", SceneComponent_removeChild },
    { "AttachTo", SceneComponent_attachTo },
    { "Detach", SceneComponent_detach },
    { "SetLocation", SceneComponent_setLocation },
    { "SetRotation", SceneComponent_setRotation },
    { 0, 0 }
};

static int sceneComponent_ctor(lua_State* L)
{
    int first_top = lua_gettop(L);
    // if (lua_gettop(L) != 1) return -1; // ?
    SceneComponent* comp = LuaObject<SceneComponent>::constructor(L);
    SET_METATABLE(L, LUCUS_LUA_SCENE_COMPONENT_CLASS)
    int top = lua_gettop(L);
    return 1;
}

static const luaL_Reg sceneComponent_meta[] = {
    { "__index", &LuaObject<SceneComponent>::index },
    { "__gc", &LuaObject<SceneComponent>::destructor },
    { 0, 0 }
};
    
int MeshComponent_setMesh(lua_State* L)
{
    LuaStack stack(L);
    MeshComponent* comp = stack.GetLuaObject<MeshComponent>(1);
    cc8* meshName = stack.GetValue<cc8*>(2, "");
    if (comp != nullptr)
    {
        comp->SetMesh(meshName);
    }
    return 0;
}

int MeshComponent_setImage(lua_State* L)
{
    LuaStack stack(L);
    MeshComponent* comp = stack.GetLuaObject<MeshComponent>(1);
    cc8* imageName = stack.GetValue<cc8*>(2, "");
    if (comp != nullptr)
    {
        comp->SetImage(imageName);
    }
    return 0;
}

static const luaL_Reg meshComponent_methods[] = {
    { "SetImage", MeshComponent_setImage },
    { "SetMesh", MeshComponent_setMesh },
    { 0, 0 }
};

static int meshComponent_ctor(lua_State* L)
{
    // if (lua_gettop(L) != 1) return -1; // ?
    MeshComponent* comp = LuaObject<MeshComponent>::constructor(L);
    SET_METATABLE(L, LUCUS_LUA_MESH_COMPONENT_CLASS)
    return 1;
}

static const luaL_Reg meshComponent_meta[] = {
    { "__index", &LuaObject<MeshComponent>::index },
    { "__gc", &LuaObject<MeshComponent>::destructor },
    { 0, 0 }
};

static int cameraComponent_ctor(lua_State* L)
{
    // if (lua_gettop(L) != 1) return -1; // ?
    CameraComponent* comp = LuaObject<CameraComponent>::constructor(L);
    SET_METATABLE(L, LUCUS_LUA_CAMERA_COMPONENT_CLASS)
    return 1;
}

static const luaL_Reg cameraComponent_meta[] = {
    { "__index", &LuaObject<CameraComponent>::index },
    { "__gc", &LuaObject<CameraComponent>::destructor },
    { 0, 0 }
};

static int springArmComponent_ctor(lua_State* L)
{
    // if (lua_gettop(L) != 1) return -1; // ?
    SpringArmComponent* comp = LuaObject<SpringArmComponent>::constructor(L);
    SET_METATABLE(L, LUCUS_LUA_SPRING_ARM_COMPONENT_CLASS)
    return 1;
}

static const luaL_Reg springArmComponent_meta[] = {
    { "__index", &LuaObject<SpringArmComponent>::index },
    { "__gc", &LuaObject<SpringArmComponent>::destructor },
    { 0, 0 }
};

namespace LucusEngine
{
    void InitializeComponents(LuaState* state)
    {
        lua_State* L = state->GetRawLua();

        LUA_NAMESPACE(L, LUCUS_LUA_MAIN_MODULE);
        ADD_CTOR(L, LUCUS_LUA_SCENE_COMPONENT_CLASS, sceneComponent_ctor);
        ADD_CTOR(L, LUCUS_LUA_MESH_COMPONENT_CLASS, meshComponent_ctor);
        ADD_CTOR(L, LUCUS_LUA_CAMERA_COMPONENT_CLASS, cameraComponent_ctor);
        ADD_CTOR(L, LUCUS_LUA_SPRING_ARM_COMPONENT_CLASS, springArmComponent_ctor);

        ADD_METATABLE(L, LUCUS_LUA_SCENE_COMPONENT_CLASS, sceneComponent_methods, sceneComponent_meta);
        ADD_INH_METATABLE(L, LUCUS_LUA_MESH_COMPONENT_CLASS, sceneComponent_methods, meshComponent_methods, meshComponent_meta);
        ADD_METATABLE(L, LUCUS_LUA_CAMERA_COMPONENT_CLASS, sceneComponent_methods, cameraComponent_meta);
        ADD_METATABLE(L, LUCUS_LUA_SPRING_ARM_COMPONENT_CLASS, sceneComponent_methods, springArmComponent_meta);

        // lua_pop(L, 4); // meta
        lua_pop(L, 1); // global
    }
}
