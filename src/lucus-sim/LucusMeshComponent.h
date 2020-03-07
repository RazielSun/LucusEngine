//
//  LucusMeshComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 5/03/2020.
//

#ifndef _LUCUS_ENGINE_MESH_COMPONENT_H
#define _LUCUS_ENGINE_MESH_COMPONENT_H

#include "LucusTypes.h"

namespace LucusEngine
{
	class Mesh;

    class MeshComponent
    {
    public:
        MeshComponent();
        virtual ~MeshComponent();

    protected:
    	Mesh* mMesh;
    };
}

#endif /* _LUCUS_ENGINE_MESH_COMPONENT_H */
