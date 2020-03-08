//
//  LucusMath.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 07/03/2020.
//

#include "LucusMath.h"
#include <cstring>
#include <math.h>

//float FVector2::operator[] (u32 i) const
//{
//    return *(&x+i);
//}
//
//float& FVector2::operator[] (u32 i)
//{
//    return *(&x+i);
//}

const FMatrix4x4 FMatrix4x4::Identity {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

FMatrix4x4::FMatrix4x4()
{
    memset(_m, 0, sizeof(_m));
}

FMatrix4x4::FMatrix4x4(const FMatrix4x4& mtx)
{
    memcpy(_m, mtx._m, sizeof(_m));
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
    float fovRad = (fov * PI) / 180.0f;
    float ys = 1 / tan(fovRad * 0.5);
    float xs = ys / aspect;
//    float zs = farZ / (farZ - nearZ);
    float zs = farZ / (nearZ - farZ);
    
    FMatrix4x4 mtx;
    mtx.m[0][0] = xs;
    mtx.m[1][1] = ys;
//    mtx.m[2][2] = 1;
    mtx.m[2][2] = zs;
    mtx.m[2][3] = -1;
    mtx.m[3][2] = nearZ * zs;
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
    FVector3 r;
    return r;
}
    
//#if defined(TARGET_METAL)
//simd::float4 FMatrix4x4::operator * (const simd::float4& vec) const
//{
//    simd::float4 r = vec;
//    return r;
//}
//#endif

void FMatrix4x4::SetTranslate(float x, float y, float z)
{
//    m[0][3] = x;
//    m[1][3] = y;
//    m[2][3] = z;
    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
}

void FMatrix4x4::SetTranslate(const FVector3& v)
{
    SetTranslate(v.x, v.y, v.z);
}

#if defined(TARGET_METAL)
//static simd::float4 operator*(const simd::float4 x, const FMatrix4x4 y)
//{
//    simd::float4 r = x;
//    return r;
//}
//simd::float4 operator * (const DEVICE_Q FMatrix4x4& mtx, const DEVICE_Q simd::float4& vec)
//{
//    simd::float4 r = vec;
//    return r;
//}
//
//simd::float4 operator * (const DEVICE_Q simd::float4& vec, const DEVICE_Q FMatrix4x4& mtx)
//{
//    simd::float4 r = vec;
//    return r;
//}
#endif


