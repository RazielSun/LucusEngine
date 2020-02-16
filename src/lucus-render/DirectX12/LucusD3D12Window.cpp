
#include "LucusD3D12Window.h"

using namespace LucusEngine;

D3D12Window::D3D12Window(u32 width, u32 height) : RenderWindow(width, height)
{
}

D3D12Window::~D3D12Window()
{
    //
}

void D3D12Window::ChangeViewportSize(u32 width, u32 height)
{
    mWidth = width;
    mHeight = height;
}

void D3D12Window::SetCoreWindow(Windows::UI::Core::CoreWindow^ window)
{
    mWindow = window;
}