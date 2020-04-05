//
//  LucusVector.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 01/04/2020.
//

#include "LucusVector.h"
#include "LucusMath.h"

using namespace LucusEngine;

const FVector2 FVector2::Zero { 0.0f, 0.0f };

float FVector2::operator[] (u32 i) const
{
    return *(&x+i);
}

float& FVector2::operator[] (u32 i)
{
    return *(&x+i);
}

const FVector3 FVector3::Zero { 0.0f, 0.0f, 0.0f };
const FVector3 FVector3::One { 1.0f, 1.0f, 1.0f };

float FVector3::operator[] (u32 i) const
{
    return *(&x+i);
}

float& FVector3::operator[] (u32 i)
{
    return *(&x+i);
}

float FVector3::GetLength() const
{
	return FMath::Sqrt(x*x + y*y + z*z);
}

void FVector3::Normalize()
{
	float length = GetLength();
	x /= length;
	y /= length;
	z /= length;
}

FVector3 FVector3::GetNormalized() const
{
	FVector3 v(*this);
	v.Normalize();
	return v;
}

const FVector4 FVector4::Zero { 0.0f, 0.0f, 0.0f, 0.0f };

float FVector4::operator[] (u32 i) const
{
    return *(&x+i);
}

float& FVector4::operator[] (u32 i)
{
    return *(&x+i);
}
