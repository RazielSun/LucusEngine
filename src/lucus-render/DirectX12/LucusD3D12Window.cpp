
#include "LucusD3D12Window.h"

using namespace DX;

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

	// TODO
	mViewport = CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(mWidth), static_cast<float>(mHeight));
	mScissorRect = CD3DX12_RECT(0, 0, static_cast<LONG>(mWidth), static_cast<LONG>(mHeight));
}

void D3D12Window::CreateDescriptorHeap(D3D12Device& device)
{
    // Create descriptor heaps for render target views and depth stencil views.
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = c_frameCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	DX::ThrowIfFailed(device.mD3D12Device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(mRTVHeap.ReleaseAndGetAddressOf())));

	mRTVDescriptorSize = device.mD3D12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

void D3D12Window::CreateWindowSizeDependentResources(D3D12Device& device)
{
    //if (!m_window)
	//{
	//	throw std::exception("Call SetWindow with a valid CoreWindow pointer.");
	//}

	// Wait until all previous GPU work is complete.
	// WaitForGpu();

	for (u32 n = 0; n < c_frameCount; n++)
	{
		mRenderTargets[n] = nullptr;
		// m_fenceValues[n] = m_fenceValues[m_currentFrame];
	}

	UINT backBufferWidth = static_cast<UINT>(GetWidth());
	UINT backBufferHeight = static_cast<UINT>(GetHeight());
	DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	if (mSwapChain)
	{
		// If the swap chain already exists, resize it.
		HRESULT hr = mSwapChain->ResizeBuffers(c_frameCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

		// Check here hr
	}
	else
	{
		// Create a descriptor for swap chain.
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = backBufferWidth;
		swapChainDesc.Height = backBufferHeight;
		swapChainDesc.Format = backBufferFormat;
		swapChainDesc.SampleDesc.Count = 1;							// Don't use multi-sampling.
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = c_frameCount;					// Use triple-buffering to minimize latency.
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	// All Windows Universal apps must use _FLIP_ SwapEffects.
		swapChainDesc.Flags = 0;
		swapChainDesc.Scaling = DXGI_SCALING_ASPECT_RATIO_STRETCH;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

		// Create swap chain for the window;
		ComPtr<IDXGISwapChain1> swapChain;
		ThrowIfFailed(device.mDXGIFactory->CreateSwapChainForCoreWindow(
			device.mCommandQueue.Get(),
			reinterpret_cast<IUnknown*>(mWindow.Get()),
			&swapChainDesc,
			nullptr,
			swapChain.GetAddressOf()
		));

		ThrowIfFailed(swapChain.As(&mSwapChain));
	}

	{
		// m_currentFrame = mSwapChain->GetCurrentBackBufferIndex();

		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = backBufferFormat;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

		for (u32 n = 0; n < c_frameCount; n++)
		{
			ThrowIfFailed(mSwapChain->GetBuffer(n, IID_PPV_ARGS(mRenderTargets[n].GetAddressOf())));

			CD3DX12_CPU_DESCRIPTOR_HANDLE rtvDescriptor(mRTVHeap->GetCPUDescriptorHandleForHeapStart(), static_cast<UINT>(n), mRTVDescriptorSize);

			device.mD3D12Device->CreateRenderTargetView(mRenderTargets[n].Get(), nullptr, rtvDescriptor);
		}
	}
}