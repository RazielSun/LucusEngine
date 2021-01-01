//
//  LucusScene.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#ifndef _LUCUS_ENGINE_SCENE_H
#define _LUCUS_ENGINE_SCENE_H

#include "LucusTypes.h"

namespace LucusEngine
{
	class World;
    class ICamera;

	class SceneComponent;
	// class CameraComponent;
	// class MeshComponent;

    class SceneComponentProxy;

    class Scene
    {
    protected:
    	World* mWorld;
        
        std::vector<ICamera*> mCameras;
        ICamera* mDefaultCam;
        int CurrentCameraIndex;

        

    public:
        Scene(World* world);
        ~Scene();

        void AddSceneComponent(SceneComponent* );
        void RemoveSceneComponent(SceneComponent* );

        ICamera* GetCamera() const;
    
    public:
        std::vector<SceneComponent*> PendingComponents;
        std::vector<SceneComponent*> RemoveComponents;
        std::vector<SceneComponentProxy*> Proxies;

            // List of components
            // std::vector<MeshComponent*> MeshComps;
    //        CameraComponent* CameraComp;
            
            
    };
}

#endif /* _LUCUS_ENGINE_SCENE_H */
