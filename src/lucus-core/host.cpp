//
//  host.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 11/02/2020.
//

#include "host.h"
#include "LucusCore.h"
#include "LucusRenderCore.h"
#include "LucusFileSystem.h"

#include "LucusLuaStack.h"
#include "LucusLuaState.h"

void AKUCoreCreate()
{
    // Init Engine
    LucusEngine::Core* core = new LucusEngine::Core();
}

void AKUCoreDestroy()
{
    LucusEngine::Core* core = new LucusEngine::Core();
    if (core)
    {
        delete core;
    }
}

void AKUGetApplicationSize(u32& width, u32& height)
{
    LucusEngine::LuaState* state = LucusEngine::Core::GetModule<LucusEngine::LuaState>();
    if (nullptr != state)
    {
        LucusEngine::LuaStack stack(state->GetRawLua());
        stack.PushGlobalTable("application");
        stack.PushValueByName("width", -1);
        width = stack.GetValue<u32>(-1, 0);
        stack.Pop();
        stack.PushValueByName("height", -1);
        height = stack.GetValue<u32>(-1, 0);
        stack.Pop(2);
    }
}

void AKUGetApplicationTitle(std::string& title)
{
    LucusEngine::LuaState* state = LucusEngine::Core::GetModule<LucusEngine::LuaState>();
    if (nullptr != state)
    {
        LucusEngine::LuaStack stack(state->GetRawLua());
        stack.PushGlobalTable("application");
        stack.PushValueByName("title", -1);
        title = stack.GetValue<cc8*>(-1, "None");
        stack.Pop(2);
    }
}

void AKUCreateRenderSystem(u32 width, u32 height)
{
    LucusEngine::RenderSystem* system = CreateRenderSystem(width, height);
    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
    if (core != nullptr)
    {
        core->SetRenderSystem(system);
    }
}

//void AKUCreateWorld()
//{
//    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
//    if (core != nullptr)
//    {
//        core->CreateWorld();
//    }
//}

void AKUCreateLua()
{
    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
    if (core != nullptr)
    {
        core->CreateLua();
    }
}

void AKURun()
{
    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
    if (core != nullptr)
    {
        core->Run();
    }
}

void AKUTick()
{
    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
    if (core != nullptr)
    {
        core->Tick();
    }
}

void AKUChangeViewportSize(u32 width, u32 height)
{
    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
    if (core != nullptr)
    {
        core->ChangeViewportSize(width, height);
    }
}

void AKUChangeWorkingDir(char const* path)
{
    LucusEngine::Core::GetFileSystem()->ChangeWorkingDir(path);
}
