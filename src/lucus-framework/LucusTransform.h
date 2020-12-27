//
//  LucusTransform.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 3/03/2020.
//

#ifndef _LUCUS_ENGINE_TRANSFORM_H
#define _LUCUS_ENGINE_TRANSFORM_H

#include "LucusTypes.h"
#include "LucusVector.h"
#include "LucusQuaternion.h"
#include "LucusRotator.h"
#include "LucusMatrix.h"

namespace LucusEngine
{
    class Transform
    {
    public:
        Transform();
        Transform(FVector3 Location, FQuaternion Rotation, FVector3 Scale);
        ~Transform();

        void SetLocation(float x, float y, float z);
        void SetLocation(const FVector3& vec);
        void AddLocation(float x, float y, float z);
        const FVector3& GetLocation() const { return mLocation; }

        // void SetRotationEuler(float x, float y, float z);
        void SetRotation(float roll, float pitch, float yaw);
        void SetRotation(const FRotator& rot);
        void SetRotation(const FQuaternion& quat);
        const FQuaternion& GetRotation() const { return mRotation; }
        // const FVector3& GetRotationEuler() const { return mRotationEuler; }
        void Rotate(const FVector3& axis, float angle);

        void SetScale(float scale);
        void SetScale(float x, float y, float z);
        void SetScale(const FVector3& vec);
        const FVector3& GetScale() const { return mScale; }

        void UpdateMatrices();
        void UpdateRotateMatrix(const FVector3& axis, float angle);
        const FMatrix4x4& GetModelMatrix() const { return mModelMatrix; }

    protected:
    	FVector3 mLocation;
        FQuaternion mRotation;
        // FVector3 mRotationEuler;
        FVector3 mScale;
        
        bool mIsDirty;

    	FMatrix4x4 mModelMatrix;
        FMatrix4x4 mTranslateMatrix;
        FMatrix4x4 mRotateMatrix;
        FMatrix4x4 mScaleMatrix;
    };
}

#endif /* _LUCUS_ENGINE_TRANSFORM_H */
