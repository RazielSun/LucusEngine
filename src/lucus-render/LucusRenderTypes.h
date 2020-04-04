//
//  LucusRenderTypes.h
//  LucusGame
//
//  Created by Alexander Kardakov on 13/02/2020.
//

#ifndef _LUCUS_ENGINE_RENDER_TYPES_H
#define _LUCUS_ENGINE_RENDER_TYPES_H

//namespace LucusEngine
//{
#if defined(TARGET_METAL)
#   include <simd/simd.h>

    typedef struct
    {
        matrix_float4x4 MVP_MATRIX;
        matrix_float4x4 PROJ_MATRIX;
        matrix_float4x4 VIEW_MATRIX;
        matrix_float4x4 MODEL_MATRIX;
    } Uniforms;

#elif defined(TARGET_DX12)
#   include <DirectXMath.h>

    typedef struct
    {
        DirectX::XMFLOAT4X4 MVP_MATRIX;
        DirectX::XMFLOAT4X4 PROJ_MATRIX;
        DirectX::XMFLOAT4X4 VIEW_MATRIX;
        DirectX::XMFLOAT4X4 MODEL_MATRIX;
    } Uniforms;

#endif
//}

#endif /* _LUCUS_ENGINE_RENDER_TYPES_H */
