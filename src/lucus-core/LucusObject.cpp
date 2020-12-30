//
//  LucusObject.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 28/12/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#include "LucusObject.h"

using namespace LucusEngine;

Object::~Object()
{
	assert(counter == 0);
}

void Object::AddRef()
{
	counter++;
}

void Object::ReleaseRef()
{
	counter--;
	if (counter == 0)
	{
		delete this;
	}
}