//
//  LucusTransform.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 3/03/2020.
//

#include "LucusTransform.h"

using namespace LucusEngine;

Transform::Transform() noexcept :
	mLocation(FVector3::Zero),
	mRotation(FQuaternion::Identity),
//	mRotationEuler(FVector3::Zero),
	mScale(FVector3::One),
	mModelMatrix(FMatrix4x4::Identity),
    mIsDirty(true)
{
}

Transform::Transform(FVector3 Location, FQuaternion Rotation, FVector3 Scale) noexcept :
    mLocation(Location),
    mRotation(Rotation),
    mScale(Scale),
    mModelMatrix(FMatrix4x4::Identity),
    mIsDirty(true)
{
    UpdateMatrices();
}

Transform::~Transform() noexcept
{
    //
}

void Transform::SetLocation(float x, float y, float z)
{
	mLocation = FVector3(x, y, z);
    mIsDirty = true;
}

void Transform::SetLocation(const FVector3& vec)
{
	mLocation = vec;
    mIsDirty = true;
}

void Transform::AddLocation(float x, float y, float z)
{
	mLocation.x += x;
	mLocation.y += y;
	mLocation.z += z;
    mIsDirty = true;
}

// void Transform::SetRotationEuler(float x, float y, float z)
// {
// 	mRotationEuler = FVector3(x, y, z);
// 	// mRotation
// }

void Transform::SetRotation(float roll, float pitch, float yaw)
{
	mRotation.Set(roll, pitch, yaw);
    mIsDirty = true;
}

void Transform::SetRotation(const FRotator& rot)
{
	SetRotation(rot.roll, rot.pitch, rot.yaw);
}

void Transform::SetRotation(const FQuaternion& quat)
{
	mRotation = quat;
    mIsDirty = true;
}

void Transform::Rotate(const FVector3& axis, float angle)
{
    mRotation.RotateAroundAxis(axis, angle);
    mIsDirty = true;
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

//void Transform::UpdateRotateMatrix(const FVector3& axis, float angle)
//{
//	mRotateMatrix.RotateAround(axis, angle);
//    mIsDirty = true;
//}

void Transform::UpdateMatrices()
{
    if (mIsDirty)
    {
        mIsDirty = false;
        FMatrix4x4 TranslateMatrix(FMatrix4x4::Identity);
        TranslateMatrix.SetTranslate(mLocation);
        
        FMatrix4x4 RotateMatrix(FMatrix4x4::Identity);
        RotateMatrix.SetRotate(mRotation);
        
        FMatrix4x4 ScaleMatrix(FMatrix4x4::Identity);
        ScaleMatrix.SetScale(mScale);

        mModelMatrix = TranslateMatrix * RotateMatrix * ScaleMatrix;
    }
}

void Transform::SetCachedWorldMatrix(const FMatrix4x4& mtx)
{
    mCachedWorldMatrix = mtx;
}
