//
//  LucusViewport.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 6/03/2020.
//

#include "LucusViewport.h"

using namespace LucusEngine;

Viewport::Viewport(float left, float top, float width, float height) :
	mLeft(left),
	mTop(top),
	mWidth(width),
	mHeight(height)
{
    //
}

Viewport::Viewport() : Viewport(0.0f, 0.0f, 0.0f, 0.0f)
{
    //
}

Viewport::~Viewport()
{
}

void Viewport::ChangeSize(float width, float height)
{
	mWidth = width;
	mHeight = height;
}

void Viewport::ChangeOirigin(float left, float top)
{
	mLeft = left;
	mTop = top;
}
