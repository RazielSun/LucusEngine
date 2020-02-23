//
//  DefaultShader.metal
//  LucusGame
//
//  Created by Alexander Kardakov on 13/02/2020.
//

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

#include "LucusShaderTypes.h"

typedef struct
{
    float4 position [[position]];
    float4 color;
} DefaultRasterizerData;

vertex DefaultRasterizerData defaultVertexShader(uint vertexID [[vertex_id]], constant DefaultVertex* vertices [[buffer(0)]])
{
    DefaultRasterizerData out;
    
    out.position = float4( 0, 0, 0, 1 );
    out.position.xy = vertices[vertexID].position;
    out.color = vertices[vertexID].color;
    
    return out;
}

fragment float4 defaultFragmentShader(DefaultRasterizerData in [[stage_in]])
{
    return in.color;
}

//
typedef struct
{
    float3 position [[attribute(0)]];
} SimpleVertexIn;

typedef struct
{
    float4 position [[position]];
} RasterizerData;

vertex RasterizerData simpleVertexShader(SimpleVertexIn in [[stage_in]])
{
    RasterizerData out;
    
    out.position = float4( 0, 0, 0, 1 );
    out.position.xyz = in.position;
    
    return out;
}

fragment float4 simpleFragmentShader(RasterizerData in [[stage_in]])
{
    return float4(0,0,0,1);
}
