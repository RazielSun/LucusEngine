//
//  LucusMeshFormat.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 22/02/2020.
//

#ifndef _LUCUS_ENGINE_MESH_FORMAT_H
#define _LUCUS_ENGINE_MESH_FORMAT_H

#include "LucusTypes.h"

namespace LucusEngine
{
    class Mesh;

    class MeshFormat
    {
    public:
        MeshFormat();
        virtual ~MeshFormat();
        
        virtual void LoadMesh(Mesh* mesh, cc8* name) = 0;
    };
}

#endif /* _LUCUS_ENGINE_MESH_FORMAT_H */
