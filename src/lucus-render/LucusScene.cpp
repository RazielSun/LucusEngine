//
//  LucusScene.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#include "LucusScene.h"
#include "LucusWorld.h"
#include "LucusSceneComponentProxy.h"
#include "LucusSceneComponent.h"

#include "LucusViewCamera.h"

#include "LucusMeshComponent.h"
#include "LucusCameraComponent.h"

using namespace LucusEngine;

Scene::Scene(World* world) : mWorld(world), mDefaultCam(new ViewCamera()), CurrentCameraIndex(-1)
{
    //
}

Scene::~Scene()
{
    delete mDefaultCam;
    mWorld = nullptr;
}

void Scene::AddSceneComponent(SceneComponent* comp)
{
    // if (nullptr != comp)
    // {
    // 	MeshComponent* meshComp = dynamic_cast<MeshComponent*>(comp);
    // 	if (nullptr != meshComp)
    // 	{
    // 		MeshComps.push_back(meshComp);
    //         return;
    // 	}

//		if (CameraComp == nullptr)
//		{
//			CameraComp = dynamic_cast<CameraComponent*>(comp);
//		}
    // }

    if (nullptr != comp)
    {
        ICamera* camPtr = dynamic_cast<ICamera*>(comp);
        if (camPtr != nullptr)
        {
            mCameras.push_back(camPtr);
            CurrentCameraIndex++;
        }
        else
        {
            PendingComponents.push_back(comp);

            const ChildrenVector& children = comp->GetChildren();
            for (auto& child : children)
            {
                AddSceneComponent(child.Get());
            }
        }
    }
}

void Scene::RemoveSceneComponent(SceneComponent* comp)
{
    if (nullptr != comp)
    {
        //
    }
}

ICamera* Scene::GetCamera() const
{
    if (CurrentCameraIndex == -1)
        return mDefaultCam;
    return mCameras[CurrentCameraIndex];
}
