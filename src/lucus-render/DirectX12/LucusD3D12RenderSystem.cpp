
#include "LucusD3D12RenderSystem.h"

#include <chrono> // for time

using namespace DX;

using Microsoft::WRL::ComPtr;

using namespace LucusEngine;

D3D12RenderSystem::D3D12RenderSystem() :
    mDevice(this),
    m_currentFrame(0),
	m_rtvDescriptorSize(0),
    m_d3dMinFeatureLevel(D3D_FEATURE_LEVEL_11_0)
{
    //
}

D3D12RenderSystem::~D3D12RenderSystem()
{
    //
}

RenderWindow* D3D12RenderSystem::CreateRenderWindow(u32 width, u32 height)
{
    // Create Device
    CreateDeviceResources();

    mWindow = new D3D12Window(width, height);

    mWindows.push_back(static_cast<RenderWindow*>(mWindow));

    return mWindows.front();
}

void D3D12RenderSystem::CreateBuffers()
{
    //
}

void D3D12RenderSystem::Render()
{
    // Prepare device resources
	auto commandAllocator = m_commandAllocators[m_currentFrame];
	auto renderTarget = m_renderTargets[m_currentFrame];

	// Reset command allocator
	commandAllocator->Reset();

	// Get CommandList and reset
	m_commandList->Reset(commandAllocator.Get(), nullptr);

	// Transition render target into correct state to allow draw into it.
	{
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(renderTarget.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		m_commandList->ResourceBarrier(1, &barrier);

		FLOAT clearColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtv(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_currentFrame, m_rtvDescriptorSize);

		// Clear render target
    	m_commandList->ClearRenderTargetView(rtv, clearColor, 0, nullptr);
	}
	
	// Sets

	// Draw

	// Transition render target into correct state to present.
	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(renderTarget.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m_commandList->ResourceBarrier(1, &barrier);

	// Present
	// Set command list off to the GPU
	ThrowIfFailed(m_commandList->Close());
	m_commandQueue->ExecuteCommandLists(1, CommandListCast(m_commandList.GetAddressOf()));

	ThrowIfFailed(m_swapChain->Present(1, 0));
	
	// Next Frame
	MoveToNextFrame();
}
        
void D3D12RenderSystem::ChangeViewportSize(u32 width, u32 height)
{
    //
}

void D3D12RenderSystem::Tick()
{
    static uint64_t frameCounter = 0;
    static double elapsedSeconds = 0.0;
    static std::chrono::high_resolution_clock clock;
    static auto t0 = clock.now();
 
    frameCounter++;
    auto t1 = clock.now();
    auto deltaTime = t1 - t0;
    t0 = t1;

	elapsedSeconds += deltaTime.count() * 1e-9;
    if (elapsedSeconds > 1.0)
    {
        // char buffer[500];
        // auto fps = frameCounter / elapsedSeconds;
        // sprintf_s(buffer, 500, "FPS: %f\n", fps);
        // OutputDebugString(buffer);
        frameCounter = 0;
        elapsedSeconds = 0.0;
    }

	// Don't try render in first frame
	// if (m_frameCount == 0)
	// {
	// 	return;
	// }

	if (frameCounter != 0)
		Render();
}

// Wait for pending GPU work to complete.
void D3D12RenderSystem::WaitForGpu()
{
    // Schedule a Signal command in the queue.
	ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), m_fenceValues[m_currentFrame]));

	// Wait until the fence has been crossed.
	ThrowIfFailed(m_fence->SetEventOnCompletion(m_fenceValues[m_currentFrame], m_fenceEvent));
	WaitForSingleObjectEx(m_fenceEvent, INFINITE, FALSE);

	// Increment the fence value for the current frame.
	m_fenceValues[m_currentFrame]++;
}

// Prepare to render the next frame.
void D3D12RenderSystem::MoveToNextFrame()
{
    // Schedule a Signal command in the queue.
    const UINT64 currentFenceValue = m_fenceValues[m_currentFrame];
    ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), currentFenceValue));

    // Update the back buffer index.
    m_currentFrame = m_swapChain->GetCurrentBackBufferIndex();

    // If the next frame is not ready to be rendered yet, wait until it is ready.
    if (m_fence->GetCompletedValue() < m_fenceValues[m_currentFrame])
    {
        ThrowIfFailed(m_fence->SetEventOnCompletion(m_fenceValues[m_currentFrame], m_fenceEvent));
        WaitForSingleObjectEx(m_fenceEvent, INFINITE, FALSE);
    }

    // Set the fence value for the next frame.
    m_fenceValues[m_currentFrame] = currentFenceValue + 1;
}

void D3D12RenderSystem::CreateDeviceResources()
{
    #if defined(_DEBUG)
	{
		// Enable debug layer interface before create dx device
		ComPtr<ID3D12Debug> debugController;
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
		debugController->EnableDebugLayer();
	}
#endif

	UINT createFactoryFlags = 0;
#if defined(_DEBUG)
	createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif
    ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&m_dxgiFactory)));
    
    ComPtr<IDXGIAdapter1> adapter;
    GetAdapter(adapter.GetAddressOf());

    ThrowIfFailed(D3D12CreateDevice(adapter.Get(), m_d3dMinFeatureLevel, IID_PPV_ARGS(m_d3dDevice.ReleaseAndGetAddressOf())));

	// Enable debug messages in debug mode.
#if defined(_DEBUG)
    ComPtr<ID3D12InfoQueue> pInfoQueue;
    if (SUCCEEDED(m_d3dDevice.As(&pInfoQueue)))
    {
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE);
        // Suppress whole categories of messages
        //D3D12_MESSAGE_CATEGORY Categories[] = {};
 
        // Suppress messages based on their severity level
        D3D12_MESSAGE_SEVERITY Severities[] =
        {
            D3D12_MESSAGE_SEVERITY_INFO
        };
 
        // Suppress individual messages by their ID
        D3D12_MESSAGE_ID DenyIds[] = {
            D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,   // I'm really not sure how to avoid this message.
            D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,                         // This warning occurs when using capture frame while graphics debugging.
            D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,                       // This warning occurs when using capture frame while graphics debugging.
        };
 
        D3D12_INFO_QUEUE_FILTER NewFilter = {};
        //NewFilter.DenyList.NumCategories = _countof(Categories);
        //NewFilter.DenyList.pCategoryList = Categories;
        NewFilter.DenyList.NumSeverities = _countof(Severities);
        NewFilter.DenyList.pSeverityList = Severities;
        NewFilter.DenyList.NumIDs = _countof(DenyIds);
        NewFilter.DenyList.pIDList = DenyIds;
 
        ThrowIfFailed(pInfoQueue->PushStorageFilter(&NewFilter));
    }
#endif

	// Create the command queue.
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    ThrowIfFailed(m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(m_commandQueue.ReleaseAndGetAddressOf())));

	// Create descriptor heaps for render target views and depth stencil views.
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = c_frameCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	DX::ThrowIfFailed(m_d3dDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(m_rtvHeap.ReleaseAndGetAddressOf())));

	m_rtvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	// Create command allocators for each back buffer
	for (UINT n = 0; n < c_frameCount; n++)
	{
		ThrowIfFailed(m_d3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_commandAllocators[n].ReleaseAndGetAddressOf())));
	}

	// Create command list for recording graphics commands
	ThrowIfFailed(m_d3dDevice->CreateCommandList(0,D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocators[0].Get(), nullptr, IID_PPV_ARGS(m_commandList.ReleaseAndGetAddressOf())));
	ThrowIfFailed(m_commandList->Close());

	// Create synchronization objects.
	ThrowIfFailed(m_d3dDevice->CreateFence(m_fenceValues[m_currentFrame], D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
	m_fenceValues[m_currentFrame]++;

	m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (m_fenceEvent == nullptr)
	{
		ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
	}
}

// These resources need to be recreated every time the window size is changed.
void D3D12RenderSystem::CreateWindowSizeDependentResources()
{
    //if (!m_window)
	//{
	//	throw std::exception("Call SetWindow with a valid CoreWindow pointer.");
	//}

	// Wait until all previous GPU work is complete.
	WaitForGpu();

	for (UINT n = 0; n < c_frameCount; n++)
	{
		m_renderTargets[n] = nullptr;
		m_fenceValues[n] = m_fenceValues[m_currentFrame];
	}

	UINT backBufferWidth = static_cast<UINT>(mWindow->GetWidth());
	UINT backBufferHeight = static_cast<UINT>(mWindow->GetHeight());
	DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;

	if (m_swapChain)
	{
		// If the swap chain already exists, resize it.
		HRESULT hr = m_swapChain->ResizeBuffers(c_frameCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

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
		ThrowIfFailed(m_dxgiFactory->CreateSwapChainForCoreWindow(
			m_commandQueue.Get(),
			reinterpret_cast<IUnknown*>(mWindow->mWindow.Get()),
			&swapChainDesc,
			nullptr,
			swapChain.GetAddressOf()
		));

		ThrowIfFailed(swapChain.As(&m_swapChain));
	}

	{
		m_currentFrame = m_swapChain->GetCurrentBackBufferIndex();

		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = backBufferFormat;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

		for (UINT n = 0; n < c_frameCount; n++)
		{
			ThrowIfFailed(m_swapChain->GetBuffer(n, IID_PPV_ARGS(m_renderTargets[n].GetAddressOf())));

			CD3DX12_CPU_DESCRIPTOR_HANDLE rtvDescriptor(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), static_cast<UINT>(n), m_rtvDescriptorSize);

			m_d3dDevice->CreateRenderTargetView(m_renderTargets[n].Get(), nullptr, rtvDescriptor);
		}
	}
}

// This method is called when the CoreWindow is created (or re-created).
void D3D12RenderSystem::SetCoreWindow(Windows::UI::Core::CoreWindow^ window)
{
    if (mWindow == nullptr)
    {
        u32 width = static_cast<u32>(window->Bounds.Width);
        u32 height = static_cast<u32>(window->Bounds.Height);
        CreateRenderWindow(width, height);
    }
    mWindow->SetCoreWindow(window);

	CreateWindowSizeDependentResources();
}

void D3D12RenderSystem::GetAdapter(IDXGIAdapter1** ppAdapter)
{
	ComPtr<IDXGIAdapter1> adapter;
	*ppAdapter = nullptr;

	for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != m_dxgiFactory->EnumAdapters1(adapterIndex, &adapter); adapterIndex++)
	{
		DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			// Don't select the Basic Render Driver adapter.
			continue;
		}

		// Check to see if the adapter supports Direct3D 12, but don't create the
		// actual device yet.
		if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), m_d3dMinFeatureLevel, _uuidof(ID3D12Device), nullptr)))
		{
			break;
		}
	}

	*ppAdapter = adapter.Detach();
}