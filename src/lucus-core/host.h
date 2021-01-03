//
//  host.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 11/02/2020.
//

#ifndef _LUCUS_ENGINE_HOST_H
#define _LUCUS_ENGINE_HOST_H

#include "LucusTypes.h"

void AKUCoreCreate();
void AKUCoreDestroy();

void AKUCreateRenderSystem(u32 width, u32 height);
void AKUCreateWorld();
void AKUCreateLua();
void AKURunLua(cc8* path);

void AKURun();
void AKUTick();

void AKUChangeViewportSize(u32 width, u32 height);
void AKUChangeWorkingDir(char const* path);

#endif /* _LUCUS_ENGINE_HOST_H */
