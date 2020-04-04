//
//  LucusVector.h
//  LucusGame
//
//  Created by Alexander Kardakov on 01/04/2020.
//

#ifndef _LUCUS_ENGINE_VECTOR_H
#define _LUCUS_ENGINE_VECTOR_H

#include "LucusTypes.h"

namespace LucusEngine
{
	struct FVector2
	{
		static const FVector2 Zero;
	    static const u32 ELEMENT_COUNT = 2;
	    
	    float x, y;
	    
	    FVector2() = default;
	    FVector2(const FVector2& v) : x(v.x), y(v.y) {}
	    constexpr FVector2(float _x, float _y) : x(_x), y(_y) {}
	    
	    float operator[] (u32 i) const;
	    float& operator[] (u32 i);
	};

	struct FVector3
	{
		static const FVector3 Zero;
	    static const u32 ELEMENT_COUNT = 3;
	    
	    float x, y, z;
	    
	    FVector3() = default;
	    FVector3(const FVector3& v) : x(v.x), y(v.y), z(v.z) {}
	    constexpr FVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	    
	    float operator[] (u32 i) const;
	    float& operator[] (u32 i);
	};

	struct FVector4
	{
		static const FVector4 Zero;
	    static const u32 ELEMENT_COUNT = 4;
	    
	    float x, y, z, w;
	    
	    FVector4() = default;
	    FVector4(const FVector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	    constexpr FVector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	    
	    float operator[] (u32 i) const;
	    float& operator[] (u32 i);
	};
}

#endif /* _LUCUS_ENGINE_VECTOR_H */