//
//  LucusQuaternion.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 01/04/2020.
//

#include "LucusQuaternion.h"

using namespace LucusEngine;

FQuaternion::FQuaternion(const float array[])
{
	x = array[0]; y = array[1]; z = array[2]; w = array[3];
}