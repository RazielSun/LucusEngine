//
//  LucusWindow.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 12/02/2020.
//

#include "LucusRenderWindow.h"

using namespace LucusEngine;

RenderWindow::RenderWindow(u32 width, u32 height) :
	mViewport( 0.0f, 0.0f, width, height )
{
    //
}

RenderWindow::RenderWindow() : RenderWindow ( 0, 0 )
{
    //
}

RenderWindow::~RenderWindow()
{
    //
}
