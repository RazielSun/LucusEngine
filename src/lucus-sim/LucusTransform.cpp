//
//  LucusTransform.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 3/03/2020.
//

#include "LucusTransform.h"

using namespace LucusEngine;

Transform::Transform() : mLocation(0,0,0)
{
    //
}

Transform::~Transform()
{
    //
}

void Transform::SetLocation(float x, float y, float z)
{
	mLocation = FVector3(x, y, z);
}

void Transform::AddLocation(float x, float y, float z)
{
	mLocation.x += x;
	mLocation.y += y;
	mLocation.z += z;
}

void Transform::UpdateModelMatrix()
{
	//
}