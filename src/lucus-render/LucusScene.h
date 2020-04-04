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
	class SceneComponent;
	class CameraComponent;
	class MeshComponent;

    class Scene
    {
    protected:
    	World* mWorld;
    
    public:
    	// List of components
    	std::vector<MeshComponent*> MeshComps;
    	CameraComponent* CameraComp;

    public:
        Scene(World* world);
        ~Scene();

        void AddSceneComponent(SceneComponent* );
        void RemoveSceneComponent(SceneComponent* );
    };
}

#endif /* _LUCUS_ENGINE_SCENE_H */
