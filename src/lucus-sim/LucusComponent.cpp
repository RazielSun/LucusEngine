//
//  LucusComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/03/2020.
//

#include "LucusComponent.h"
#include "LucusComponentProxy.h"

using namespace LucusEngine;

Component::Component() :
	mTransform(),
    Proxy(nullptr)
{
    //
}

Component::~Component()
{
    //
}
