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

void AKUCreateRenderSystem(u32 width, u32 height)
{
    LucusEngine::RenderSystem* system = CreateRenderSystem(width, height);
    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
    if (core != nullptr)
    {
        core->SetRenderSystem(system);
    }
}

void AKUCreateWorld()
{
    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
    if (core != nullptr)
    {
        core->CreateWorld();
    }
}

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
