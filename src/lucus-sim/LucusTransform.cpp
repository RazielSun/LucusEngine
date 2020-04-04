//
//  LucusTransform.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 3/03/2020.
//

#include "LucusTransform.h"

using namespace LucusEngine;

Transform::Transform() :
	mLocation(0,0,0),
	mRotation(0,0,0,1),
	mRotationEuler(0,0,0),
	mScale(1,1,1),
	mModelMatrix(FMatrix4x4::Identity),
	mTranslateMatrix(FMatrix4x4::Identity),
	mRotateMatrix(FMatrix4x4::Identity),
	mScaleMatrix(FMatrix4x4::Identity)
{
}

Transform::~Transform()
{
    //
}

void Transform::SetLocation(float x, float y, float z)
{
	mLocation = FVector3(x, y, z);
}

void Transform::SetLocation(const FVector3& vec)
{
	mLocation = vec;
}

void Transform::AddLocation(float x, float y, float z)
{
	mLocation.x += x;
	mLocation.y += y;
	mLocation.z += z;
}

void Transform::SetRotationEuler(float x, float y, float z)
{
	mRotationEuler = FVector3(x, y, z);
	// mRotation
}

void Transform::SetRotation(float pitch, float roll, float yaw)
{
	//mRotation
	//mRotationEuler
}

void Transform::SetRotation(const FQuaternion& quat)
{
	mRotation = quat;
	//mRotationEuler
}

void Transform::SetScale(float scale)
{
	mScale = FVector3(scale, scale, scale);
}

void Transform::SetScale(float x, float y, float z)
{
	mScale = FVector3(x, y, z);
}

void Transform::SetScale(const FVector3& vec)
{
	mScale = vec;
}

void Transform::UpdateMatrices()
{
    mModelMatrix.SetTranslate(mLocation);
}
