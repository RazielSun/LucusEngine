
#include "LucusD3D12Device.h"

using namespace DX;

using namespace LucusEngine;

D3D12Device::D3D12Device(D3D12RenderSystem* renderSystem) :
    mRenderSystem(renderSystem),
    mD3DMinFeatureLevel(D3D_FEATURE_LEVEL_11_0)
{
    //
}

D3D12Device::~D3D12Device()
{
    ReleaseAll();
}

void D3D12Device::ReleaseAll()
{
    mD3D12Device.Reset();
}

void D3D12Device::Init()
{
    ReleaseAll();

    UINT createFactoryFlags = 0;
#if defined(_DEBUG)
	createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif
    ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&mDXGIFactory)));
    
    ComPtr<IDXGIAdapter1> adapter;
    GetAdapter(adapter.GetAddressOf());

    ThrowIfFailed(D3D12CreateDevice(adapter.Get(), mD3DMinFeatureLevel, IID_PPV_ARGS(mD3D12Device.ReleaseAndGetAddressOf())));

    	// Enable debug messages in debug mode.
#if defined(_DEBUG)
    ComPtr<ID3D12InfoQueue> pInfoQueue;
    if (SUCCEEDED(mD3D12Device.As(&pInfoQueue)))
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

    ThrowIfFailed(mD3D12Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(mCommandQueue.ReleaseAndGetAddressOf())));
	mCommandQueue->SetName(L"Command Queue");

    // Create command allocators for each back buffer
	for (u32 n = 0; n < c_frameCount; n++)
	{
		ThrowIfFailed(mD3D12Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(mCommandAllocators[n].ReleaseAndGetAddressOf())));
	}

	// Create command list for recording graphics commands
	ThrowIfFailed(mD3D12Device->CreateCommandList(0,D3D12_COMMAND_LIST_TYPE_DIRECT, mCommandAllocators[0].Get(), nullptr, IID_PPV_ARGS(mCommandList.ReleaseAndGetAddressOf())));
	ThrowIfFailed(mCommandList->Close());
	mCommandList->SetName(L"Command List");
}

void D3D12Device::GetAdapter(IDXGIAdapter1** ppAdapter)
{
	ComPtr<IDXGIAdapter1> adapter;
	*ppAdapter = nullptr;

	for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != mDXGIFactory->EnumAdapters1(adapterIndex, &adapter); adapterIndex++)
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
		if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), mD3DMinFeatureLevel, _uuidof(ID3D12Device), nullptr)))
		{
			break;
		}
	}

	*ppAdapter = adapter.Detach();
}