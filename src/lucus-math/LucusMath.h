//
//  LucusMath.h
//  LucusGame
//
//  Created by Alexander Kardakov on 13/02/2020.
//

#ifndef _LUCUS_ENGINE_MATH_H
#define _LUCUS_ENGINE_MATH_H

#include "LucusTypes.h"

#define PI 3.14159265

#if defined(TARGET_METAL)
#include <simd/simd.h>
#elif defined(TARGET_DX12)
#   include <DirectXMath.h>
#endif

struct FVector2
{
    static const u32 ELEMENT_COUNT = 2;
    
    float x, y;
    
    FVector2() = default;
    constexpr FVector2(float _x, float _y) : x(_x), y(_y) {}
    
    float operator[] (u32 i) const;
    float& operator[] (u32 i);
};

struct FVector3
{
    static const u32 ELEMENT_COUNT = 3;
    
    float x, y, z;
    
    FVector3() = default;
    constexpr FVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    
    float operator[] (u32 i) const;
    float& operator[] (u32 i);
};

struct FVector4
{
    static const u32 ELEMENT_COUNT = 4;
    
    float x, y, z, w;
    
    FVector4() = default;
    constexpr FVector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    
    float operator[] (u32 i) const;
    float& operator[] (u32 i);
};

struct FMatrix4x4
{
    static const FMatrix4x4 Identity;
    
    static const u32 ROW_COUNT = 4;
    static const u32 ELEMENT_COUNT = 16;
    
    union {
        float m[ROW_COUNT][ROW_COUNT];
        float _m[ELEMENT_COUNT];
    };
    
    FMatrix4x4();
    FMatrix4x4(const FMatrix4x4& mtx);
    explicit FMatrix4x4(const float array[]);
    FMatrix4x4( float m11, float m12, float m13, float m14,
                float m21, float m22, float m23, float m24,
                float m31, float m32, float m33, float m34,
                float m41, float m42, float m43, float m44
               );
    
 #if defined(TARGET_METAL)
    matrix_float4x4 GetNative() const {
        return (matrix_float4x4) {{
            { m[0][0], m[0][1], m[0][2], m[0][3] },
            { m[1][0], m[1][1], m[1][2], m[1][3] },
            { m[2][0], m[2][1], m[2][2], m[2][3] },
            { m[3][0], m[3][1], m[3][2], m[3][3] }
        }};
        
    }
#elif defined(TARGET_DX12)
	DirectX::XMFLOAT4X4 GetNative() const {
		return { 
			m[0][0], m[0][1], m[0][2], m[0][3],
			m[1][0], m[1][1], m[1][2], m[1][3],
			m[2][0], m[2][1], m[2][2], m[2][3],
			m[3][0], m[3][1], m[3][2], m[3][3]
		};
	}
#endif
    
    static FMatrix4x4 RightHandProjectionMatrix(float aspect, float nearZ, float farZ, float fov);
    
    FMatrix4x4 operator * (const FMatrix4x4& mtx) const;
    FVector3 operator * (const FVector3& vec) const;
    
    void SetTranslate(float x, float y, float z);
    void SetTranslate(const FVector3& v);
};

#endif /* _LUCUS_ENGINE_MATH_H */
