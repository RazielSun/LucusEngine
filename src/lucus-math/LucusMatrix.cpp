//
//  LucusMatrix.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 01/04/2020.
//

#include "LucusMatrix.h"
#include "LucusMemory.h"
#include "LucusMath.h"
#include "LucusVector.h"
#include "LucusQuaternion.h"
// #include <cstring>
// #include <math.h>

using namespace LucusEngine;

const FMatrix4x4 FMatrix4x4::Identity {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

FMatrix4x4::FMatrix4x4()
{
    // memset(_m, 0, sizeof(_m));
    Memory::MemSet(_m, 0, sizeof(_m));
}

FMatrix4x4::FMatrix4x4(const FMatrix4x4& mtx)
{
    // memcpy(_m, mtx._m, sizeof(_m));
    Memory::MemCpy(_m, mtx._m, sizeof(_m));
}

FMatrix4x4::FMatrix4x4(const float array[])
{
    for (u32 i = 0; i < 16; ++i)
        _m[i] = array[i];
}

FMatrix4x4::FMatrix4x4(float m11, float m12, float m13, float m14,
                       float m21, float m22, float m23, float m24,
                       float m31, float m32, float m33, float m34,
                       float m41, float m42, float m43, float m44)
{
    m[0][0] = m11; m[0][1] = m12; m[0][2] = m13; m[0][3] = m14;
    m[1][0] = m21; m[1][1] = m22; m[1][2] = m23; m[1][3] = m24;
    m[2][0] = m31; m[2][1] = m32; m[2][2] = m33; m[2][3] = m34;
    m[3][0] = m41; m[3][1] = m42; m[3][2] = m43; m[3][3] = m44;
}

FMatrix4x4 FMatrix4x4::RightHandProjectionMatrix(float aspect, float nearZ, float farZ, float fov)
{
    float fovRad = fov * D2R;
    float ys = 1.0f / (float)tan(fovRad * 0.5);
    float xs = ys / aspect;
    float zs = farZ / (nearZ - farZ);
    
    FMatrix4x4 mtx;
    mtx.m[0][0] = xs;
    mtx.m[1][1] = ys;
    mtx.m[2][2] = zs;
	mtx.m[2][3] = nearZ * zs;
	mtx.m[3][2] = -1;
    return mtx;
}

FMatrix4x4 FMatrix4x4::operator * (const FMatrix4x4& mtx) const
{
    FMatrix4x4 r;
    for (u32 i = 0; i < ROW_COUNT; ++i)
    {
        for (u32 j = 0; j < ROW_COUNT; ++j)
        {
            for (u32 k = 0; k < ROW_COUNT; ++k)
            {
                r.m[i][j] += m[i][k] * mtx.m[k][j];
            }
        }
    }
    return r;
}

FVector3 FMatrix4x4::operator * (const FVector3& vec) const
{
    FVector3 r = vec;
    return r;
}

void FMatrix4x4::SetTranslate(float x, float y, float z)
{
    m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
}

void FMatrix4x4::SetTranslate(const FVector3& v)
{
    SetTranslate(v.x, v.y, v.z);
}

void FMatrix4x4::SetRotate(const FQuaternion& quat)
{
    quat.ToRotateMatrix(*this);
}

void FMatrix4x4::RotateAround(const FVector3& axis, float rad)
{
    FVector3 N = axis.GetNormalized();
    float C = FMath::Cos(rad);
    float S = FMath::Sin(rad);
    float CI = 1 - C;

    float x = N.x;
    float y = N.y;
    float z = N.z;

    // memset(_m, 0, sizeof(_m));
    Memory::MemSet(_m, 0, sizeof(_m));

    m[0][0] = x * x * CI + C;
    m[0][1] = x * y * CI - z * S;
    m[0][2] = x * z * CI + y * S;
    m[1][0] = x * y * CI + z * S;
    m[1][1] = y * y * CI + C;
    m[1][2] = y * z * CI - x * S;
    m[2][0] = x * z * CI - y * S;
    m[2][1] = y * z * CI + x * S;
    m[2][2] = z * z * CI + C;
    m[3][3] = 1;
}

void FMatrix4x4::SetScale(float scale)
{
    m[0][0] = scale;
    m[1][1] = scale;
    m[2][2] = scale;
}

void FMatrix4x4::SetScale(float x, float y, float z)
{
    m[0][0] = x;
    m[1][1] = y;
    m[2][2] = z;
}

void FMatrix4x4::SetScale(const FVector3& v)
{
    m[0][0] = v.x;
    m[1][1] = v.y;
    m[2][2] = v.z;
}
