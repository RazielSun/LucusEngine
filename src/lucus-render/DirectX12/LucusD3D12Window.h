//
//  LucusD3D12Window.h
//  LucusGame
//
//  Created by Alexander Kardakov on 15/02/2020.
//

#ifndef _LUCUS_ENGINE_D3D12_WINDOW_H
#define _LUCUS_ENGINE_D3D12_WINDOW_H

#include "LucusD3D12Prerequisites.h"
#include "LucusRenderWindow.h"
#include "LucusD3D12Device.h"

#include <agile.h>

namespace LucusEngine
{
    class D3D12Window : public RenderWindow
    {
    public:
        D3D12Window(u32 width, u32 height);
        virtual ~D3D12Window();

        virtual void ChangeViewportSize(u32 width, u32 height) override;

        void SetCoreWindow(Windows::UI::Core::CoreWindow^ window);

        void CreateDescriptorHeap(D3D12Device& device);
        void CreateWindowSizeDependentResources(D3D12Device& device);

    // private:
        // Cached reference to the Window.
		Platform::Agile<Windows::UI::Core::CoreWindow>	mWindow;

        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	mRTVHeap;

        u32											    mRTVDescriptorSize;

        Microsoft::WRL::ComPtr<IDXGISwapChain3>			mSwapChain;
		Microsoft::WRL::ComPtr<ID3D12Resource>			mRenderTargets[c_frameCount];

		CD3DX12_VIEWPORT								mViewport;
		CD3DX12_RECT									mScissorRect;
    };
}

#endif /* _LUCUS_ENGINE_D3D12_WINDOW_H */