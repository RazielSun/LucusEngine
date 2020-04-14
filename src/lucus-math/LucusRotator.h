//
//  LucusRotator.h
//  LucusGame
//
//  Created by Alexander Kardakov on 13/04/2020.
//

#ifndef _LUCUS_ENGINE_ROTATOR_H
#define _LUCUS_ENGINE_ROTATOR_H

#include "LucusTypes.h"

namespace LucusEngine
{
	struct FRotator
	{
		static const FRotator Zero;
		
		float roll, pitch, yaw;

		FRotator() : roll(0.0f), pitch(0.0f), yaw(0.0f) {}
		FRotator(float _roll, float _pitch, float _yaw) : roll(_roll), pitch(_pitch), yaw(_yaw) {}

	};
}

#endif /* _LUCUS_ENGINE_ROTATOR_H */
