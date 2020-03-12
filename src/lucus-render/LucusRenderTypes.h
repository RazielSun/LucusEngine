//
//  LucusRenderTypes.h
//  LucusGame
//
//  Created by Alexander Kardakov on 13/02/2020.
//

#ifndef _LUCUS_ENGINE_RENDER_TYPES_H
#define _LUCUS_ENGINE_RENDER_TYPES_H

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
	//FMatrix4x4 MVP_MATRIX;
	//FMatrix4x4 PROJ_MATRIX;
	//FMatrix4x4 VIEW_MATRIX;
	//FMatrix4x4 MODEL_MATRIX;
} Uniforms;

#endif

#endif /* _LUCUS_ENGINE_RENDER_TYPES_H */
