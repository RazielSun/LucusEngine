//
//  LucusVector.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 01/04/2020.
//

#include "LucusVector.h"

using namespace LucusEngine;

float FVector2::operator[] (u32 i) const
{
    return *(&x+i);
}

float& FVector2::operator[] (u32 i)
{
    return *(&x+i);
}

float FVector3::operator[] (u32 i) const
{
    return *(&x+i);
}

float& FVector3::operator[] (u32 i)
{
    return *(&x+i);
}

float FVector4::operator[] (u32 i) const
{
    return *(&x+i);
}

float& FVector4::operator[] (u32 i)
{
    return *(&x+i);
}