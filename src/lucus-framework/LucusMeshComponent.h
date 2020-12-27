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
        MeshComponent();
        MeshComponent(cc8* meshName);
        MeshComponent(cc8* meshName, cc8* imageName);
        virtual ~MeshComponent();
        
        virtual void Init(const tinyxml2::XMLElement*) override;
        
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