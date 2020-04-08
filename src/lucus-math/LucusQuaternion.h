//
//  LucusQuaternion.h
//  LucusGame
//
//  Created by Alexander Kardakov on 01/04/2020.
//

#ifndef _LUCUS_ENGINE_QUATERNION_H
#define _LUCUS_ENGINE_QUATERNION_H

#include "LucusTypes.h"

namespace LucusEngine
{
	struct FVector3;
    struct FMatrix4x4;

	struct FQuaternion
	{
		static const FQuaternion Identity;

		static const u32 ELEMENT_COUNT = 4;
		
		// [s,v], where s = w, v = xi + yk + zk
		float w, x, y, z;

		// Identity Quaternion with 0 angle
		FQuaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
		FQuaternion(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {}
		FQuaternion(const FQuaternion& quat) : w(quat.w), x(quat.x), y(quat.y), z(quat.z) {}
		explicit FQuaternion(const float array[]);
		FQuaternion(const FVector3& axis, float angleRad);

		float operator[] (u32 i) const;
	    float& operator[] (u32 i);
        
        void ToRotateMatrix(FMatrix4x4& mtx) const;
        void RotateAroundAxis(const FVector3& axis, float angleRad);
	};
}

#endif /* _LUCUS_ENGINE_QUATERNION_H */
