//
//  LucusVertexTypes.h
//  LucusGame
//
//  Created by Alexander Kardakov on 01/04/2020.
//

#ifndef _LUCUS_ENGINE_VERTEX_TYPES_H
#define _LUCUS_ENGINE_VERTEX_TYPES_H

#include "LucusTypes.h"
#include "LucusVector.h"

namespace LucusEngine
{
	struct TriangleIndex
	{
	    u32 x, y, z;
	    
	    TriangleIndex() : x(0), y(0), z(0) {}
	    TriangleIndex(u32 _x, u32 _y, u32 _z) : x(_x), y(_y), z(_z) {}
	    
	    bool operator==(const TriangleIndex& other) const
	    {
	        return other.x == x && other.y == y && other.z == z;
	    }
	};

	struct SimpleVertex
	{
	    FVector3 position;
	    FVector2 texcoord;
	};
}

namespace std
{
    template<>
    struct hash<LucusEngine::TriangleIndex>
    {
        size_t operator()(const LucusEngine::TriangleIndex& v) const
        {
            return ((hash<u32>()(v.x)) ^ (hash<u32>()(v.y) << 1) >> 1) ^ (hash<u32>()(v.z) << 1);
        }
    };
}

#endif /* _LUCUS_ENGINE_VERTEX_TYPES_H */