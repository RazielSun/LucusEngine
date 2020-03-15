
#include "LucusD3D12RenderSystem.h"
#include "LucusRenderTypes.h"
#include "LucusD3D12ComponentProxy.h"
#include "LucusScene.h"
#include "LucusCore.h"

#include "LucusCameraComponent.h"
#include "LucusMeshComponent.h"
#include <DirectXMath.h>

using namespace DX;
using namespace LucusEngine;

D3D12RenderSystem::D3D12RenderSystem() :
    mDevice(this),
    mCurrentFrame(0),
	mReady(false)
{
}

D3D12RenderSystem::~D3D12RenderSystem()
{
    // temp
	// if (nullptr != mMesh)
	// {
	// 	delete mMesh;
	// 	mMesh = nullptr;
	// }
}

RenderWindow* D3D12RenderSystem::CreateRenderWindow(u32 width, u32 height)
{
	CreateDevice();

    mWindow = new D3D12Window(width, height);

    mWindows.push_back(static_cast<RenderWindow*>(mWindow));

	//CreateBuffers();

    return mWindows.front();
}

void D3D12RenderSystem::CreateBuffers()
{
	// Prepare device resources
	auto commandAllocator = mDevice.mCommandAllocators[mCurrentFrame];
	auto commandList = mDevice.mCommandList;
	// Reset command allocator
	commandAllocator->Reset();
	// Get CommandList and reset
	commandList->Reset(commandAllocator.Get(), nullptr);

	// Create Assets
    for (auto* component : mScene->MeshComps) {
        D3D12ComponentProxy* proxy = new D3D12ComponentProxy(&mDevice);
        proxy->CreateBuffers(component->GetMesh());
        component->Proxy = proxy;
    }

	// TEST
	// Create constant buffer
	const u32 constantBufferSize = sizeof(Uniforms);
	CD3DX12_RESOURCE_DESC constantBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(constantBufferSize);

	ThrowIfFailed(mDevice.mD3D12Device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&constantBufferDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&mConstantBuffer)));

	D3D12_CONSTANT_BUFFER_VIEW_DESC constantBufferViewDesc = {};
	constantBufferViewDesc.BufferLocation = mConstantBuffer->GetGPUVirtualAddress();
	constantBufferViewDesc.SizeInBytes = constantBufferSize;

	mDevice.mD3D12Device->CreateConstantBufferView(&constantBufferViewDesc, mDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	// Map the constant buffers.
	//ZeroMemory(&mMappedDataAddress, sizeof(mMappedDataAddress));
	ThrowIfFailed(mConstantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&mMappedDataAddress)));

	//Uniforms uniforms;
	//memcpy()

	{
		// Map the constant buffers.
		//CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
		//ThrowIfFailed(mConstantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&mMappedDataAddress)));
	}

	// Close the command list and execute it to begin the vertex/index buffer copy into the GPU's default heap.
	DX::ThrowIfFailed(commandList->Close());
	ID3D12CommandList* ppCommandLists[] = { commandList.Get() };
	mDevice.mCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	// Wait for GPU, otherwise the buffer might not be uploaded by the time we start drawing
	WaitForGpu();

	mReady = true;
}

void D3D12RenderSystem::Render()
{
	if (!mReady) return;

	//if (!mCBVready)
	//{
	//	mCBVready = true;

	//	D3D12_CONSTANT_BUFFER_VIEW_DESC constantBufferViewDesc = {};
	//	constantBufferViewDesc.BufferLocation = mConstantBuffer->GetGPUVirtualAddress();
	//	constantBufferViewDesc.BufferLocation = sizeof(Uniforms);

	//	//
	//	mDevice.mD3D12Device->CreateConstantBufferView(&constantBufferViewDesc, mDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
	//}

	// Update Uniforms

	Uniforms uniforms;
	CameraComponent* cameraCom = mScene->CameraComp;
	cameraCom->UpdateProjectionMatrix(mWindow->GetViewport());

	Viewport viewport = mWindow->GetViewport();

	// This sample makes use of a right-handed coordinate system using row-major matrices.
	//uniforms.PROJ_MATRIX = cameraCom->GetProjMatrix().GetNative();
	float aspectRatio = viewport.GetAspectRatio();
	uniforms.PROJ_MATRIX = {
			1, 0, 0, 0,
			0, aspectRatio, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	};
	uniforms.VIEW_MATRIX = cameraCom->GetTransform().GetModelMatrix().GetNative();
	auto* component = mScene->MeshComps[0];
	component->GetTransform().UpdateModelMatrix();
	uniforms.MODEL_MATRIX = component->GetTransform().GetModelMatrix().GetNative();

	//for (auto* component : mScene->MeshComps) {
	//	component->GetTransform().UpdateModelMatrix();
	//	component->Proxy->UpdateUniforms(uniforms, component->GetTransform());
	//}
	
	memcpy(mMappedDataAddress, &uniforms, sizeof(Uniforms));

	// Start Frame

    // Prepare device resources
	auto commandAllocator = mDevice.mCommandAllocators[mCurrentFrame];
	auto renderTarget = mWindow->mRenderTargets[mCurrentFrame];
	auto commandList = mDevice.mCommandList;

	// Reset command allocator
	commandAllocator->Reset();

	// Get CommandList and reset
	commandList->Reset(commandAllocator.Get(), nullptr);

	// BEGIN Set Frame

	//Viewport viewport = mWindow->GetViewport();
	CD3DX12_VIEWPORT cViewport(0.0f, 0.0f, viewport.GetWidth(), viewport.GetHeight());
	CD3DX12_RECT cScissorRect(
		static_cast<LONG>(viewport.GetLeft()),
		static_cast<LONG>(viewport.GetTop()),
		static_cast<LONG>(viewport.GetRight()),
		static_cast<LONG>(viewport.GetBottom())
	);
	commandList->RSSetViewports(1, &cViewport);
	commandList->RSSetScissorRects(1, &cScissorRect);

	// Transition render target into correct state to allow draw into it.
	{
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(renderTarget.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		commandList->ResourceBarrier(1, &barrier);
	}
	
	//
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(mWindow->mRTVHeap->GetCPUDescriptorHandleForHeapStart(), mCurrentFrame, mWindow->mRTVDescriptorSize);
	commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
	
	// Clear render target
	FLOAT clearColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	// Set Main Descriptor Heaps
	ID3D12DescriptorHeap* descriptorHeaps[] = { mDescriptorHeap.Get() };
	commandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	 // Set Shader Signature
	commandList->SetGraphicsRootSignature(mRootSignature.Get());

	// Set PSO
	commandList->SetPipelineState(mPipelineState.Get());

	// Bind constant buffer
	// Bind the current frame's constant buffer to the pipeline.
	//CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(mDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),mCurrentFrame, mDescriptorSize);
	//commandList->SetGraphicsRootDescriptorTable(0, gpuHandle);
	commandList->SetGraphicsRootDescriptorTable(0, mDescriptorHeap->GetGPUDescriptorHandleForHeapStart());

	// //Set quad data
	//commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//commandList->IASetVertexBuffers(0, 1, &mVertexBufferView);
	// // Draw
	//commandList->DrawInstanced(6, 1, 0, 0);

	for (auto* component : mScene->MeshComps) {
		if (component->Proxy)
		{
			D3D12ComponentProxy* proxy = static_cast<D3D12ComponentProxy*>(component->Proxy);
			if (proxy)
			{
				proxy->DrawIndexed(commandList);
			}
		}
    }

	// Transition render target into correct state to present.
	{
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(renderTarget.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
		commandList->ResourceBarrier(1, &barrier);
	}

	// END

	// Present
	// Set command list off to the GPU
	ThrowIfFailed(commandList->Close());

	//
	mDevice.mCommandQueue->ExecuteCommandLists(1, CommandListCast(commandList.GetAddressOf()));

	//
	ThrowIfFailed(mWindow->mSwapChain->Present(1, 0));
	
	// Next Frame
	MoveToNextFrame();
}
        
void D3D12RenderSystem::ChangeViewportSize(u32 width, u32 height)
{
    if (mWindow != nullptr)
	{
		//mWindow->ChangeViewportSize(width, height);
		RenderSystem::ChangeViewportSize(width, height);

		// Wait until all previous GPU work is complete.
		WaitForGpu();

		// Window Dependent Resources
		ResetFenceValues();
		// These resources need to be recreated every time the window size is changed.
		mWindow->CreateWindowSizeDependentResources(mDevice);
		mCurrentFrame = mWindow->mSwapChain->GetCurrentBackBufferIndex();
	}
}

// Wait for pending GPU work to complete.
void D3D12RenderSystem::WaitForGpu()
{
    // Schedule a Signal command in the queue.
	ThrowIfFailed(mDevice.mCommandQueue->Signal(mFence.Get(), mFenceValues[mCurrentFrame]));

	// Wait until the fence has been crossed.
	ThrowIfFailed(mFence->SetEventOnCompletion(mFenceValues[mCurrentFrame], mFenceEvent));
	WaitForSingleObjectEx(mFenceEvent, INFINITE, FALSE);

	// Increment the fence value for the current frame.
	mFenceValues[mCurrentFrame]++;
}

// Prepare to render the next frame.
void D3D12RenderSystem::MoveToNextFrame()
{
    // Schedule a Signal command in the queue.
    const UINT64 currentFenceValue = mFenceValues[mCurrentFrame];
    ThrowIfFailed(mDevice.mCommandQueue->Signal(mFence.Get(), currentFenceValue));

    // Update the back buffer index.
    mCurrentFrame = mWindow->mSwapChain->GetCurrentBackBufferIndex();

    // If the next frame is not ready to be rendered yet, wait until it is ready.
    if (mFence->GetCompletedValue() < mFenceValues[mCurrentFrame])
    {
        ThrowIfFailed(mFence->SetEventOnCompletion(mFenceValues[mCurrentFrame], mFenceEvent));
        WaitForSingleObjectEx(mFenceEvent, INFINITE, FALSE);
    }

    // Set the fence value for the next frame.
    mFenceValues[mCurrentFrame] = currentFenceValue + 1;
}

void D3D12RenderSystem::CreateDevice()
{
#if defined(_DEBUG)
	{
		// Enable debug layer interface before create dx device
		ComPtr<ID3D12Debug> debugController;
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
		debugController->EnableDebugLayer();
	}
#endif

	mDevice.Init();

	CreateDeviceDependentResources();

	// Create synchronization objects.
	ThrowIfFailed(mDevice.mD3D12Device->CreateFence(mFenceValues[0], D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence)));
	mFenceValues[0]++;

	mFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (mFenceEvent == nullptr)
	{
		ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
	}

	//CreateBuffers();
}

void D3D12RenderSystem::CreateDeviceDependentResources()
{
	// Create an empty root signature.
	//with 1 parameter for CB
	{
		CD3DX12_DESCRIPTOR_RANGE range;
		range.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

		CD3DX12_ROOT_PARAMETER parameter;
		parameter.InitAsDescriptorTable(1, &range, D3D12_SHADER_VISIBILITY_VERTEX);

		CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.Init(1, &parameter, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		ComPtr<ID3DBlob> signature;
		ComPtr<ID3DBlob> error;
		ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
		ThrowIfFailed(mDevice.mD3D12Device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&mRootSignature)));

		mRootSignature->SetName(L"Root Signature");
	}

	// Create the pipeline state, which includes compiling and loading shaders.
	{
		// ComPtr<ID3DBlob> vertexShader;
		// ComPtr<ID3DBlob> pixelShader;

// #if defined(_DEBUG)
// 		// Enable better shader debugging with the graphics debugging tools.
// 		UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
// #else
// 		UINT compileFlags = 0;
// #endif
		// Load shaders asynchronously.
		//auto createVSTask = DX::ReadDataAsync(L"DefaultVertesShader.cso").then([this](std::vector<byte>& fileData) {
		//	mVertexShader = fileData;
		//});

		//auto createPSTask = DX::ReadDataAsync(L"DefaultPixelShader.cso").then([this](std::vector<byte>& fileData) {
		//	mPixelShader = fileData;
		//});

		//auto vertexShaderData = Core::GetFileSystem()->ReadData("DefaultVertexShader.cso");
		//auto pixelShaderData = Core::GetFileSystem()->ReadData("DefaultPixelShader.cso");
		auto vertexShaderData = Core::GetFileSystem()->ReadData("SimpleVertexShader.cso");
		auto pixelShaderData = Core::GetFileSystem()->ReadData("SimplePixelShader.cso");

		// ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(L"DefaultVertesShader.cso").c_str(), nullptr, nullptr, "main", "vs_5_0", compileFlags, 0, &vertexShader, nullptr));
		//ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(L"DefaultPixelShader.cso").c_str(), nullptr, nullptr, "main", "ps_5_0", compileFlags, 0, &pixelShader, nullptr));

		// Define the vertex input layout.
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 8, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};

		// Describe and create the graphics pipeline state object (PSO).
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = mRootSignature.Get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShaderData.data(), vertexShaderData.size());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShaderData.data(), pixelShaderData.size());
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = FALSE;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = 1;
		ThrowIfFailed(mDevice.mD3D12Device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPipelineState)));

		mPipelineState->SetName(L"Pipeline State");
	}

	{
		D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = {};
		// Allocate a heap for descriptors:
		descriptorHeapDesc.NumDescriptors = 1;// c_frameCount;
		descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		descriptorHeapDesc.NodeMask = 0;
		ThrowIfFailed(mDevice.mD3D12Device->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&mDescriptorHeap)));

		mDescriptorHeap->SetName(L"Descriptor Heap");

		mDescriptorSize = mDevice.mD3D12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	}
}

void D3D12RenderSystem::ResetFenceValues()
{
	for (UINT n = 0; n < c_frameCount; n++)
	{
		// m_renderTargets[n] = nullptr;
		mFenceValues[n] = mFenceValues[mCurrentFrame];
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
		mWindow->CreateDescriptorHeap(mDevice);
    }
    mWindow->SetCoreWindow(window);

	// Wait until all previous GPU work is complete.
	WaitForGpu();

	// Window Dependent Resources
	ResetFenceValues();
	// These resources need to be recreated every time the window size is changed.
	mWindow->CreateWindowSizeDependentResources(mDevice);
	mCurrentFrame = mWindow->mSwapChain->GetCurrentBackBufferIndex();
}
