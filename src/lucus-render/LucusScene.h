//
//  LucusScene.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#ifndef _LUCUS_ENGINE_SCENE_H
#define _LUCUS_ENGINE_SCENE_H

#include "LucusTypes.h"
#include <vector>

namespace LucusEngine
{
	class World;
	class Component;
	class CameraComponent;
	class MeshComponent;

    class Scene
    {
    protected:
    	World* mWorld;

    	// List of components
    	std::vector<MeshComponent*> mMeshComps;
    	CameraComponent* mCameraComp;

    public:
        Scene(World* world);
        ~Scene();

        void AddComponent(Component* );
        void RemoveComponent(Component* );

    public:
    	CameraComponent* GetCamera() { return mCameraComp; }
    };
}

#endif /* _LUCUS_ENGINE_SCENE_H */
