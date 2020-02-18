//
//  MetalShaderTypes.h
//  LucusGame
//
//  Created by Alexander Kardakov on 13/02/2020.
//

#ifndef _LUCUS_ENGINE_SHADER_TYPES_H
#define _LUCUS_ENGINE_SHADER_TYPES_H

#if defined(TARGET_METAL)

#include <simd/simd.h>

typedef vector_float2 FVector2;
typedef vector_float4 FVector4;

#elif defined(TARGET_DX12)

#include <DirectXMath.h>

typedef DirectX::XMFLOAT2 FVector2;
typedef DirectX::XMFLOAT4 FVector4;

#else

// not properly aligned structs

struct FVector2
{
    float x, y;
};

struct FVector4
{
    float x, y, z, w;
};

#endif

typedef struct
{
    FVector2 position;
    FVector4 color;
} DefaultVertex;

#endif /* _LUCUS_ENGINE_SHADER_TYPES_H */
