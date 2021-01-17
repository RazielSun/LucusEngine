//
//  LucusMeshComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 5/03/2020.
//

#ifndef _LUCUS_ENGINE_MESH_COMPONENT_H
#define _LUCUS_ENGINE_MESH_COMPONENT_H

#include "LucusSceneComponent.h"
#include "LucusMesh.h"
#include "LucusImage.h"

namespace LucusEngine
{
    class MeshComponent : public SceneComponent
    {
    public:
        MeshComponent() noexcept;
        MeshComponent(cc8* meshName) noexcept;
        MeshComponent(cc8* meshName, cc8* imageName) noexcept;
        virtual ~MeshComponent() noexcept;
        
        void SetMesh(cc8* meshName);
        void SetImage(cc8* imageName);
        
        Mesh* GetMesh();
        Image* GetImage();

    protected:
    	MeshPtr mMesh;
        ImagePtr mImage;
    };
}

#endif /* _LUCUS_ENGINE_MESH_COMPONENT_H */
