//
//  LucusResource.h
//  LucusGame
//
//  Created by Alexander Kardakov on 08/05/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#include "LucusResource.h"

using namespace LucusEngine;

Resource::~Resource()
{
	std::assert(counter == 0);
}

void Resource::AddRef()
{
	counter++;
}

void Resource::ReleaseRef()
{
	counter--;
	if (counter == 0)
	{
		delete this;
	}
}