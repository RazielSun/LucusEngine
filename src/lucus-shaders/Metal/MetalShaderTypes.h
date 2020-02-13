//
//  MetalShaderTypes.h
//  LucusGame
//
//  Created by Alexander Kardakov on 13/02/2020.
//

#ifndef _LUCUS_ENGINE_METAL_SHADER_TYPES_H
#define _LUCUS_ENGINE_METAL_SHADER_TYPES_H

#include <simd/simd.h>

typedef struct
{
    vector_float2 position;
    vector_float4 color;
} DefaultVertex;

#endif /* _LUCUS_ENGINE_METAL_SHADER_TYPES_H */
