//
//  host.hpp
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 11/02/2020.
//

#ifndef _LUCUS_ENGINE_HOST_H
#define _LUCUS_ENGINE_HOST_H

#include "LucusTypes.h"

#include "LucusCore.h"
#include "LucusMemoryManager.h"

namespace LucusEngine
{
    class RenderSystem;
    class World;
}

void AKUCoreCreate();
void AKUCoreDestroy();

void AKUStartCoreLoop();
void AKUTick();
//void AKUUpdate();
//void AKURender();

void AKUCreateWorld(LucusEngine::World* world);

void AKUSetRenderSystem(LucusEngine::RenderSystem* system);
void AKUChangeViewportSize(u32 width, u32 height);

void AKUChangeWorkingDir(char const* path);

template<class T>
T* AKUCreateModule()
{
	return LucusEngine::Core::GetMemoryManager()->NewOnModule<T>();
}

#endif /* _LUCUS_ENGINE_HOST_H */
