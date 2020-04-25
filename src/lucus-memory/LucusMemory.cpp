//
//  LucusMemory.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 25/04/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#include "LucusMemory.h"

using namespace LucusEngine;

void Memory::MemSet(void* ptr, int value, size_t num)
{
    memset(ptr, value, num);
}

void Memory::MemCpy(void* destination, const void* source, size_t num)
{
    memcpy(destination, source, num);
}
