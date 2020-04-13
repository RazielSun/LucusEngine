//
//  LucusMath.h
//  LucusGame
//
//  Created by Alexander Kardakov on 13/02/2020.
//

#ifndef _LUCUS_ENGINE_MATH_H
#define _LUCUS_ENGINE_MATH_H

#include "LucusTypes.h"

#include <cmath>

#define M_PI 					(3.1415926535897932f)	/* Extra digits if needed: 3.1415926535897932384626433832795f */
#define D2R						( M_PI / 180.0f )
#define R2D						( 180.0f / M_PI )
// #define PI 3.14159265

// Unreal has PlatformMath and CompilerPlatformMath
namespace LucusEngine
{
    struct FMath
    {
    	static float Sin(float rad) { return sinf(rad); }
        static float Cos(float rad) { return cosf(rad); }
        static float Sqrt(float value) { return sqrtf(value); }
    };
}

#endif /* _LUCUS_ENGINE_MATH_H */
