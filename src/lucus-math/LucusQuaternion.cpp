//
//  LucusQuaternion.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 01/04/2020.
//

#include "LucusQuaternion.h"
#include "LucusVector.h"

using namespace LucusEngine;

const FQuaternion FQuaternion::Identity { 1.0f, 0.0f, 0.0f, 0.0f };

FQuaternion::FQuaternion(const float array[])
{
	x = array[0]; y = array[1]; z = array[2]; w = array[3];
}

FQuaternion::FQuaternion(const FVector3& axis, float angleRad)
{
	w = angleRad;
	x = axis.x; y = axis.y; z = axis.z;
}

float FQuaternion::operator[] (u32 i) const
{
	return *(&w+i);
}
float& FQuaternion::operator[] (u32 i)
{
	return *(&w+i);
}