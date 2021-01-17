//
//  RotatedMeshComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 06/04/2020.
//

#ifndef _ROTATED_MESH_COMPONENT_H
#define _ROTATED_MESH_COMPONENT_H

#include "LucusMeshComponent.h"

class RotatedMeshComponent : public LucusEngine::MeshComponent
{
public:
	RotatedMeshComponent() noexcept = default;
    RotatedMeshComponent(cc8* meshName, cc8* imageName) noexcept : MeshComponent(meshName, imageName) {}

	virtual void Tick(float deltaSeconds) override;

protected:
	float angle = 0.0f;
};

#endif /* _ROTATED_MESH_COMPONENT_H */
