//
//  host.cpp
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 11/02/2020.
//

#include "host.h"
#include "LucusCore.h"
#include "LucusRenderCore.h"
#include "LucusFileSystem.h"
// #include "LucusWorld.h"

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

void AKURun()
{
    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
    if (core != nullptr)
    {
        core->Run();
    }
}

// void AKUStartCoreLoop()
// {
//     LucusEngine::Core* core = LucusEngine::Core::GetPtr();
//     if (core != nullptr)
//     {
//         core->StartCoreLoop();
//     }
// }

void AKUTick()
{
    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
    if (core != nullptr)
    {
        core->Tick();
    }
}

//void AKUCreateWorld(LucusEngine::World* world)
//{
//    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
//    if (core != nullptr)
//    {
//        core->CreateWorld(world);
//    }
//}
//
//void AKUSetRenderSystem(LucusEngine::RenderSystem* system)
//{
//    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
//    if (core != nullptr)
//    {
//        core->SetRenderSystem(system);
//    }
//}

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
