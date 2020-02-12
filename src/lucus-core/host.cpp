//
//  host.cpp
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 11/02/2020.
//

#include "host.h"
#include "LucusCore.h"

void AKUCoreCreate()
{
    // Init Engine
    LucusEngine::Core* core = new LucusEngine::Core();
}

void AKUCoreDestroy()
{
    //
}

void AKUUpdate()
{
    //
}

void AKURender()
{
    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
    if (core != nullptr)
    {
        core->Render();
    }
}

void AKUSetRenderSystem(LucusEngine::RenderSystem* system)
{
    LucusEngine::Core* core = LucusEngine::Core::GetPtr();
    if (core != nullptr)
    {
        core->SetRenderSystem(system);
    }
}

void AKUChangeViewSize(int width, int height)
{
    //
}
