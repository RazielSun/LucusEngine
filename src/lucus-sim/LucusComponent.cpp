//
//  LucusComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#include "LucusComponent.h"

using namespace LucusEngine;

Component::Component()
{
    //
}

Component::~Component()
{
    //
}

bool Component::Compare(cc8* name, cc8* other)
{
    return strncmp(name, other, strlen(other)) == 0;
}
