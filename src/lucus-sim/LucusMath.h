//
//  LucusMath.h
//  LucusGame
//
//  Created by Alexander Kardakov on 13/02/2020.
//

#ifndef _LUCUS_ENGINE_MATH_H
#define _LUCUS_ENGINE_MATH_H

#if defined(TARGET_METAL)

#include <simd/simd.h>

typedef vector_float2 FVector2;
typedef vector_float3 FVector3;
typedef vector_float4 FVector4;

#elif defined(TARGET_DX12)

#include <DirectXMath.h>

typedef DirectX::XMFLOAT2 FVector2;
typedef DirectX::XMFLOAT3 FVector3;
typedef DirectX::XMFLOAT4 FVector4;

#else

// not properly aligned structs
struct FVector2
{
    float x, y;
};

struct FVector3
{
    float x, y, z;
};

struct FVector4
{
    float x, y, z, w;
};

#endif

#endif /* _LUCUS_ENGINE_MATH_H */
