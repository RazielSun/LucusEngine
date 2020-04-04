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
	struct FQuaternion
	{
		static const FQuaternion Identity;
		
		float x, y, z, w;

		FQuaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		FQuaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
		FQuaternion(const FQuaternion& quat) : x(quat.x), y(quat.y), z(quat.z), w(quat.w) {}
		explicit FQuaternion(const float array[]);
	};
}

#endif /* _LUCUS_ENGINE_QUATERNION_H */