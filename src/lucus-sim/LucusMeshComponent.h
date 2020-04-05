//
//  LucusMeshComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 5/03/2020.
//

#ifndef _LUCUS_ENGINE_MESH_COMPONENT_H
#define _LUCUS_ENGINE_MESH_COMPONENT_H

#include "LucusSceneComponent.h"

namespace LucusEngine
{
	class Mesh;
    class Image;

    class MeshComponent : public SceneComponent
    {
    public:
        MeshComponent();
        MeshComponent(cc8* meshName);
        MeshComponent(cc8* meshName, cc8* imageName);
        virtual ~MeshComponent();

        virtual void Tick(float deltaSeconds) override;
        
        Mesh* GetMesh();
        Image* GetImage();

    protected:
    	Mesh* mMesh;
        Image* mImage;

        float angle = 0.0f;
    };
}

#endif /* _LUCUS_ENGINE_MESH_COMPONENT_H */
