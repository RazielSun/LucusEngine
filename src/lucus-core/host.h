//
//  host.hpp
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 11/02/2020.
//

#ifndef _LUCUS_ENGINE_HOST_H
#define _LUCUS_ENGINE_HOST_H

#include "LucusTypes.h"

namespace LucusEngine
{
    class RenderSystem;
}

void AKUCoreCreate();
void AKUCoreDestroy();

void AKUStartCoreLoop();
void AKUTick();

void AKURun();

//void AKUUpdate();
//void AKURender();

void AKUSetRenderSystem(LucusEngine::RenderSystem* system);
void AKUChangeViewportSize(u32 width, u32 height);

void AKUChangeWorkingDir(char const* path);

#endif /* _LUCUS_ENGINE_HOST_H */
