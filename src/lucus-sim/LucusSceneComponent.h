//
//  LucusSceneComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/04/2020.
//

#ifndef _LUCUS_ENGINE_SCENE_COMPONENT_H
#define _LUCUS_ENGINE_SCENE_COMPONENT_H

#include "LucusComponent.h"
#include "LucusVector.h"
#include "LucusQuaternion.h"
#include "LucusTransform.h"
#include <vector>

namespace LucusEngine
{
    class SceneComponent;
    class SceneComponentProxy;

    typedef std::vector<SceneComponent*> ChildrenVector;
    typedef ChildrenVector::iterator ChildIt;

    class SceneComponent : public Component
    {
    public:
        SceneComponent();
        virtual ~SceneComponent();
        
        virtual void Init(const tinyxml2::XMLElement*) override;
        
        virtual void Tick(float deltaSeconds) override;
        
        SceneComponentProxy* Proxy;
        //        virtual ComponentProxy* CreateProxy();
        
        Transform& GetTransform() { return mTransform; }

        void AttachTo(SceneComponent* parent);
        void Detach();

        const ChildrenVector& GetChildren() const;
        int GetNumChildren() const;
        SceneComponent* GetParent() const; // create inline function?

    protected:
//    	FVector3 mLocation;
//        FQuaternion mRotation;
//        FVector3 mScale;

        ChildrenVector mChildren;
        SceneComponent* mParent;
        
        Transform mTransform;
    };
}

#endif /* _LUCUS_ENGINE_SCENE_COMPONENT_H */
