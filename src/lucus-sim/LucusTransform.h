//
//  LucusTransform.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 3/03/2020.
//

#ifndef _LUCUS_ENGINE_TRANSFORM_H
#define _LUCUS_ENGINE_TRANSFORM_H

#include "LucusTypes.h"
#include "LucusMath.h"

namespace LucusEngine
{
    class Transform
    {
    public:
        Transform();
        ~Transform();

        void SetLocation(float x, float y, float z);
        void AddLocation(float x, float y, float z);
        const FVector3& GetLocation() const { return mLocation; }

        void UpdateModelMatrix();
        const FMatrix4x4& GetModelMatrix() const { return mModelMatrix; }

    protected:
    	FVector3 mLocation;

    	// Rotation

    	// Scale

    	FMatrix4x4 mModelMatrix;
    };
}

#endif /* _LUCUS_ENGINE_TRANSFORM_H */
