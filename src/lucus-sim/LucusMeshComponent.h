//
//  LucusMeshComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 5/03/2020.
//

#ifndef _LUCUS_ENGINE_MESH_COMPONENT_H
#define _LUCUS_ENGINE_MESH_COMPONENT_H

#include "LucusTypes.h"
#include "LucusComponent.h"

namespace LucusEngine
{
	class Mesh;

    class MeshComponent : public Component
    {
    public:
        MeshComponent();
        MeshComponent(cc8* name);
        virtual ~MeshComponent();
        
        Mesh* GetMesh();

    protected:
    	Mesh* mMesh;
    };
}

#endif /* _LUCUS_ENGINE_MESH_COMPONENT_H */
