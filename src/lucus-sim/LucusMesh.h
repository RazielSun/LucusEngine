//
//  LucusMesh.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 22/02/2020.
//

#ifndef _LUCUS_ENGINE_MESH_H
#define _LUCUS_ENGINE_MESH_H

#include "LucusTypes.h"
#include "LucusMath.h"
#include "LucusShaderTypes.h"
#include <vector>

namespace LucusEngine
{
    struct TriangleIndex
    {
        u32 x, y, z;
    };

    struct FMeshFaceData
    {
        TriangleIndex tris[4];
        u32 count;
    };

    class Mesh
    {
        std::vector<SimpleVertex> mVertices;
        std::vector<TriangleIndex> mIndices;
        
    public:
        Mesh();
        virtual ~Mesh();
        
        void Load( cc8* name );
        void SetIndices(std::vector<TriangleIndex>& indices);
        void SetVertices(std::vector<SimpleVertex>& vertices);
    };
}

#endif /* _LUCUS_ENGINE_MESH_H */
