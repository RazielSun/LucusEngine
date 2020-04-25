//
//  LucusMemory.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 25/04/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#include "LucusMemory.h"

using namespace LucusEngine;

Memory::MemSet(void* ptr, int value, Size num)
{
    memset(ptr, value, num);
}

Memory::MemCpy(void* destination, const void* source, Size num);
{
    memcpy(destination, source, num);
}