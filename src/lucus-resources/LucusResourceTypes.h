//
//  LucusResourceTypes.h
//  LucusGame
//
//  Created by Alexander Kardakov on 09/03/2020.
//

#ifndef _LUCUS_ENGINE_RESOURCE_TYPES_H
#define _LUCUS_ENGINE_RESOURCE_TYPES_H

#include "LucusMath.h"

//typedef struct
//{
//    FVector2 position;
//    FVector4 color;
//} DefaultVertex;

//typedef FVector3 SimpleVertex;
typedef struct
{
    FVector3 position;
    FVector2 texcoord;
} SimpleVertex;

#endif /* _LUCUS_ENGINE_RESOURCE_TYPES_H */
