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
	RotatedMeshComponent();
	virtual ~RotatedMeshComponent();

	virtual void Tick(float deltaSeconds) override;

protected:
	float angle = 0.0f;
};

#endif /* _ROTATED_MESH_COMPONENT_H */
