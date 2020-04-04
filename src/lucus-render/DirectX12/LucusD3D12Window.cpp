
#include "LucusD3D12Window.h"

using namespace DX;

using namespace LucusEngine;

D3D12Window::D3D12Window(u32 width, u32 height, DXGI_FORMAT backBufferFormat, DXGI_FORMAT depthBufferFormat) :
	RenderWindow(width, height),
	mBackBufferFormat(backBufferFormat),
	mDepthBufferFormat(depthBufferFormat)
{
	// TODO
	//mViewport = CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(mWidth), static_cast<float>(mHeight));
	//mScissorRect = CD3DX12_RECT(0, 0, static_cast<LONG>(mWidth), static_cast<LONG>(mHeight));
}

D3D12Window::~D3D12Window()
{
    //
}

//void D3D12Window::ChangeViewportSize(u32 width, u32 height)
//{
//    mWidth = width;
//    mHeight = height;
//
//	// TODO
//	mViewport = CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(mWidth), static_cast<float>(mHeight));
//	mScissorRect = CD3DX12_RECT(0, 0, static_cast<LONG>(mWidth), static_cast<LONG>(mHeight));
//
//	// Change 
//}

void D3D12Window::SetCoreWindow(Windows::UI::Core::CoreWindow^ window)
{
    mWindow = window;
}

void D3D12Window::CreateDescriptorHeaps(D3D12Device& device)
{
    // Create descriptor heaps for render target views and depth stencil views.
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = c_frameCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	DX::ThrowIfFailed(device.mD3D12Device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(mRTVHeap.ReleaseAndGetAddressOf())));

	mRTVHeap->SetName(L"RTV Heap");

	mRTVDescriptorSize = device.mD3D12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	ThrowIfFailed(device.mD3D12Device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&mDSVHeap)));

	mDSVHeap->SetName(L"DSV Heap");
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

	UINT backBufferWidth = static_cast<UINT>(mViewport.GetWidth());
	UINT backBufferHeight = static_cast<UINT>(mViewport.GetHeight());
	// DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	if (mSwapChain)
	{
		// If the swap chain already exists, resize it.
		HRESULT hr = mSwapChain->ResizeBuffers(c_frameCount, backBufferWidth, backBufferHeight, mBackBufferFormat, 0);

		// Check here hr
	}
	else
	{
		// Create a descriptor for swap chain.
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = backBufferWidth;
		swapChainDesc.Height = backBufferHeight;
		swapChainDesc.Format = mBackBufferFormat;
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
		rtvDesc.Format = mBackBufferFormat;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

		for (u32 n = 0; n < c_frameCount; n++)
		{
			ThrowIfFailed(mSwapChain->GetBuffer(n, IID_PPV_ARGS(mRenderTargets[n].GetAddressOf())));

			CD3DX12_CPU_DESCRIPTOR_HANDLE rtvDescriptor(mRTVHeap->GetCPUDescriptorHandleForHeapStart(), static_cast<UINT>(n), mRTVDescriptorSize);

			device.mD3D12Device->CreateRenderTargetView(mRenderTargets[n].Get(), nullptr, rtvDescriptor);

			mRenderTargets[n]->SetName(L"RT Resource");
		}
	}

	// Create a depth stencil and view.
	{
		D3D12_HEAP_PROPERTIES depthHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

		D3D12_RESOURCE_DESC depthResourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(mDepthBufferFormat, backBufferWidth, backBufferHeight, 1, 1);
		depthResourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		CD3DX12_CLEAR_VALUE depthOptimizedClearValue(mDepthBufferFormat, 1.0f, 0);

		ThrowIfFailed(device.mD3D12Device->CreateCommittedResource(
			&depthHeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&depthResourceDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&depthOptimizedClearValue,
			IID_PPV_ARGS(&mDepthStencil)
			));

		mDepthStencil->SetName(L"Depth Stencil Resource");

		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = mDepthBufferFormat;
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

		device.mD3D12Device->CreateDepthStencilView(mDepthStencil.Get(), &dsvDesc, mDSVHeap->GetCPUDescriptorHandleForHeapStart());
	}
}