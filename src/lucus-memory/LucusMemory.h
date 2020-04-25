//
//  LucusMemory.h
//  LucusGame
//
//  Created by Alexander Kardakov on 25/04/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#ifndef _LUCUS_ENGINE_MEMORY_H
#define _LUCUS_ENGINE_MEMORY_H

#include "LucusTypes.h"

#define 10_MB (1024 * 1024 * 10)

namespace LucusEngine
{
	struct Memory
	{
		static const u8 ALIGNMENT = 16;

		static void MemSet(void* ptr, int value, Size num);

		static void MemCpy(void* destination, const void* source, Size num);
	};
}

#endif /* _LUCUS_ENGINE_MEMORY_H */