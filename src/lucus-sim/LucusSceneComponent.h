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
#include "LucusMatrix.h"
#include "LucusTransform.h"

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

        void AddChild(SceneComponent* child);
        void RemoveChild(SceneComponent* child);

        const ChildrenVector& GetChildren() const;
        u32 GetNumChildren() const;
        SceneComponent* GetParent() const; // create inline function?

        FMatrix4x4 GetModelMatrix();

    protected:
//    	FVector3 mLocation;
//        FQuaternion mRotation;
//        FVector3 mScale;

        ChildrenVector mChildren;
        SceneComponent* mParent;
        
        Transform mTransform;
    };

    FORCEINLINE const ChildrenVector& SceneComponent::GetChildren() const
    {
        return mChildren;
    }

    FORCEINLINE u32 SceneComponent::GetNumChildren() const
    {
        return (u32)mChildren.size();
    }

    FORCEINLINE SceneComponent* SceneComponent::GetParent() const
    {
        return mParent;
    }
}

#endif /* _LUCUS_ENGINE_SCENE_COMPONENT_H */
