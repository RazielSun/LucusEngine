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

    typedef std::vector<TriangleIndex> VectorIndices;
    typedef std::vector<SimpleVertex> VectorVertices;

    class Mesh
    {
        VectorVertices mVertices;
        VectorIndices mIndices;
        
    public:
        Mesh();
        virtual ~Mesh();
        
        void Load( cc8* name );
        void SetIndices(VectorIndices& indices);
        void SetVertices(VectorVertices& vertices);
        
        const VectorIndices* GetIndices() const { return &mIndices; }
        const VectorVertices* GetVertices() const { return &mVertices; }
    };
}

#endif /* _LUCUS_ENGINE_MESH_H */
