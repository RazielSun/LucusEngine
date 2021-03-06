//
//  DefaultShader.metal
//  LucusGame
//
//  Created by Alexander Kardakov on 13/02/2020.
//

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

#include "LucusRenderTypes.h"

//typedef struct
//{
//    float4 position [[position]];
//    float4 color;
//} DefaultRasterizerData;
//
//vertex DefaultRasterizerData defaultVertexShader(uint vertexID [[vertex_id]], constant DefaultVertex* vertices [[buffer(0)]])
//{
//    DefaultRasterizerData out;
//
//    out.position = float4( 0, 0, 0, 1 );
//    out.position.xy = vertices[vertexID].position;
//    out.color = vertices[vertexID].color;
//
//    return out;
//}
//
//fragment float4 defaultFragmentShader(DefaultRasterizerData in [[stage_in]])
//{
//    return in.color;
//}

//
typedef struct
{
    float3 position [[attribute(0)]];
    float2 texcoord [[attribute(1)]];
} SimpleVertexIn;

typedef struct
{
    float4 position [[position]];
    float2 texcoord;
} RasterizerData;

vertex RasterizerData simpleVertexShader(SimpleVertexIn in [[stage_in]], constant Uniforms& uniforms [[buffer(1)]])
{
    RasterizerData out;
    
    float4 position = float4( in.position.xyz, 1 );
    out.position = uniforms.MVP_MATRIX * position;
//    uniforms.MODEL_MATRIX * uniforms.VIEW_MATRIX * uniforms.PROJ_MATRIX
//    out.position = uniforms.PROJ_MATRIX * uniforms.VIEW_MATRIX * uniforms.MODEL_MATRIX * position;
    
    out.texcoord = in.texcoord;
    
    return out;
}

fragment float4 simpleFragmentShader(RasterizerData in [[stage_in]], texture2d<half> colorTexture [[ texture(0) ]])
{
    constexpr sampler textureSampler(mag_filter::linear, min_filter::linear);
    const half4 colorSample = colorTexture.sample(textureSampler, in.texcoord);
    return float4(colorSample);//float4(0,0,0,1);
}
