//
//  LucusQuaternion.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 01/04/2020.
//

#include "LucusQuaternion.h"
#include "LucusVector.h"
#include "LucusMatrix.h"
#include "LucusMath.h"

using namespace LucusEngine;

const FQuaternion FQuaternion::Identity { 1.0f, 0.0f, 0.0f, 0.0f };

FQuaternion::FQuaternion(const float array[])
{
	x = array[0]; y = array[1]; z = array[2]; w = array[3];
}

FQuaternion::FQuaternion(const FVector3& axis, float angleRad) : w(1.0f), x(0.0f), y(0.0f), z(0.0f)
{
    RotateAroundAxis(axis, angleRad);
}

float FQuaternion::operator[] (u32 i) const
{
	return *(&w+i);
}
float& FQuaternion::operator[] (u32 i)
{
	return *(&w+i);
}

void FQuaternion::ToRotateMatrix(FMatrix4x4& mtx) const
{
    // SSE optimized version
    float x2 = x + x;
    float y2 = y + y;
    float z2 = z + z;
    float xx2 = x * x2;
    float yy2 = y * y2;
    float zz2 = z * z2;
    float wx2 = w * x2;
    float wy2 = w * y2;
    float wz2 = w * z2;
    float yx2 = y * x2;
    float zx2 = z * x2;
    float zy2 = z * y2;
    
    mtx.m[0][0] = 1.0f - (yy2 + zz2);
    mtx.m[0][1] = yx2 - wz2;
    mtx.m[0][2] = zx2 + wy2;
    
    mtx.m[1][0] = yx2 + wz2;
    mtx.m[1][1] = 1.0f - (xx2 + zz2);
    mtx.m[1][2] = zy2 - wx2;
    
    mtx.m[2][0] = zx2 - wy2;
    mtx.m[2][1] = zy2 + wx2;
    mtx.m[2][2] = 1.0f - (xx2 + yy2);
}

void FQuaternion::RotateAroundAxis(const FVector3& axis, float angleRad)
{
    // axis is unit length (normalized)
    // The Quaternion representing the rotation is
    // q = cos(a/2) + sin(a/2) * (x*i + y*j + z*k)
    
    float halfAngleRad (angleRad * 0.5f);
    w = FMath::Cos(halfAngleRad);
    float S = FMath::Sin(halfAngleRad);
    x = axis.x * S;
    y = axis.y * S;
    z = axis.z * S;
}
