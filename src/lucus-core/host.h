//
//  host.hpp
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 11/02/2020.
//

#ifndef _LUCUS_ENGINE_HOST_H
#define _LUCUS_ENGINE_HOST_H

namespace LucusEngine
{
    class RenderSystem;
}

void AKUCoreCreate();
void AKUCoreDestroy();

void AKUStartCoreLoop();
void AKUTick();
//void AKUUpdate();
//void AKURender();

void AKUSetRenderSystem(LucusEngine::RenderSystem* system);
void AKUChangeViewSize(int width, int height);

#endif /* _LUCUS_ENGINE_HOST_H */
