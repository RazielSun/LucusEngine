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

inline auto operator "" _MB(u64 const x) { return 1024 * 1024 * x; }

namespace LucusEngine
{
	struct Memory
	{
		static const u8 ALIGNMENT = 16;

		static void MemSet(void* ptr, int value, size_t num);

		static void MemCpy(void* destination, const void* source, size_t num);
	};
}

#endif /* _LUCUS_ENGINE_MEMORY_H */
