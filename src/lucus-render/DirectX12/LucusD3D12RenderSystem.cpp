
#include "LucusD3D12RenderSystem.h"
#include "LucusShaderTypes.h"

#include "LucusCore.h"

#include <chrono> // for time

using namespace DX;

using namespace LucusEngine;

D3D12RenderSystem::D3D12RenderSystem() :
    mDevice(this),
    mCurrentFrame(0)
{
}

D3D12RenderSystem::~D3D12RenderSystem()
{
    // temp
	if (nullptr != mMesh)
	{
		delete mMesh;
		mMesh = nullptr;
	}
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
	mMesh = new Mesh();
	mMesh->Load("meshes/cube.fbx");

	// Define the geometry for a quad.
	// DirectX front face polygons is clockwise !!!
	//static const DefaultVertex quad[] =
	//{
	//	{ { -0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
	//	{ { 0.5f, 0.5f }, 	{ 1.0f, 1.0f, 0.0f, 1.0f } },
	//	{ { 0.5f, -0.5f }, 	{ 0.0f, 1.0f, 0.0f, 1.0f } },
	//	{ { -0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
	//	{ { -0.5f, 0.5f }, 	{ 0.0f, 0.0f, 1.0f, 1.0f } },
	//	{ { 0.5f, 0.5f }, 	{ 1.0f, 1.0f, 1.0f, 1.0f } }
	//};

	// Create the buffers.
	const std::vector<SimpleVertex>* vertices = mMesh->GetVertices();

	const u32 vertexBufferSize = static_cast<u32>(vertices->size() * sizeof(SimpleVertex));// sizeof(quad);

	// Create the vertex buffer resource in the GPU's default heap and copy vertex data into it using the upload heap.
	// The upload resource must not be released until after the GPU has finished using it.
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBufferUpload;

	CD3DX12_RESOURCE_DESC vertexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);

	CD3DX12_HEAP_PROPERTIES defaultHeapProperties(D3D12_HEAP_TYPE_DEFAULT);
	ThrowIfFailed(mDevice.mD3D12Device->CreateCommittedResource(
		&defaultHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&vertexBufferDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&mVertexBuffer)));

	CD3DX12_HEAP_PROPERTIES uploadHeapProperties(D3D12_HEAP_TYPE_UPLOAD);
	ThrowIfFailed(mDevice.mD3D12Device->CreateCommittedResource(
		&uploadHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&vertexBufferDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertexBufferUpload)));

	mVertexBuffer->SetName(L"Vertex Buffer");
	vertexBufferUpload->SetName(L"Vertex Buffer Upload");

	// Upload the vertex buffer to the GPU.
	{
		D3D12_SUBRESOURCE_DATA vertexData = {};
		vertexData.pData = reinterpret_cast<BYTE*>(const_cast<std::vector<SimpleVertex>*>(vertices)->data());
		vertexData.RowPitch = vertexBufferSize;
		vertexData.SlicePitch = vertexData.RowPitch;

		UpdateSubresources(mDevice.mCommandList.Get(), mVertexBuffer.Get(), vertexBufferUpload.Get(), 0, 0, 1, &vertexData);

		CD3DX12_RESOURCE_BARRIER vertexBufferResourceBarrier =
			CD3DX12_RESOURCE_BARRIER::Transition(mVertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
		mDevice.mCommandList->ResourceBarrier(1, &vertexBufferResourceBarrier);
	}

	// Note: using upload heaps to transfer static data like vert buffers is not 
	// recommended. Every time the GPU needs it, the upload heap will be marshalled 
	// over. Please read up on Default Heap usage. An upload heap is used here for 
	// code simplicity and because there are very few verts to actually transfer.
	//ThrowIfFailed(mDevice.mD3D12Device->CreateCommittedResource(
	//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
	//	D3D12_HEAP_FLAG_NONE,
	//	&CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&mVertexBuffer)));

	// Copy the quad data to the vertex buffer.
	//UINT8* pVertexDataBegin;
	//CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
	//ThrowIfFailed(mVertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin)));
	//memcpy(pVertexDataBegin, quad, sizeof(quad));
	//mVertexBuffer->Unmap(0, nullptr);

	//// Initialize the vertex buffer view.
	//mVertexBufferView.BufferLocation = mVertexBuffer->GetGPUVirtualAddress();
	//mVertexBufferView.StrideInBytes = sizeof(DefaultVertex);
	//mVertexBufferView.SizeInBytes = vertexBufferSize;

	const std::vector<TriangleIndex>* indices = mMesh->GetIndices();

	const u32 indicesBufferSize = static_cast<u32>(indices->size() * sizeof(TriangleIndex));
	mIndexCount = indicesBufferSize / sizeof(u32);

	Microsoft::WRL::ComPtr<ID3D12Resource> indicesBufferUpload;

	CD3DX12_RESOURCE_DESC indexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(indicesBufferSize);

	ThrowIfFailed(mDevice.mD3D12Device->CreateCommittedResource(
		&defaultHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&indexBufferDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&mIndexBuffer)));

	ThrowIfFailed(mDevice.mD3D12Device->CreateCommittedResource(
		&uploadHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&indexBufferDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indicesBufferUpload)));

	mIndexBuffer->SetName(L"Index Buffer");
	indicesBufferUpload->SetName(L"Index Buffer Upload");

	// Upload the index buffer to the GPU.
	{
		D3D12_SUBRESOURCE_DATA indexData = {};
		indexData.pData = reinterpret_cast<BYTE*>(const_cast<std::vector<TriangleIndex>*>(indices)->data());
		indexData.RowPitch = indicesBufferSize;
		indexData.SlicePitch = indexData.RowPitch;

		UpdateSubresources(mDevice.mCommandList.Get(), mIndexBuffer.Get(), indicesBufferUpload.Get(), 0, 0, 1, &indexData);

		CD3DX12_RESOURCE_BARRIER indexBufferResourceBarrier =
			CD3DX12_RESOURCE_BARRIER::Transition(mIndexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER);
		mDevice.mCommandList->ResourceBarrier(1, &indexBufferResourceBarrier);
	}

	// Close the command list and execute it to begin the vertex/index buffer copy into the GPU's default heap.
	DX::ThrowIfFailed(mDevice.mCommandList->Close());
	ID3D12CommandList* ppCommandLists[] = { mDevice.mCommandList.Get() };
	mDevice.mCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
	
	// Wait for GPU, otherwise the buffer might not be uploaded by the time we start drawing
	WaitForGpu();

	mVertexBufferView.BufferLocation = mVertexBuffer->GetGPUVirtualAddress();
	mVertexBufferView.StrideInBytes = sizeof(SimpleVertex);
	mVertexBufferView.SizeInBytes = vertexBufferSize;

	mIndexBufferView.BufferLocation = mIndexBuffer->GetGPUVirtualAddress();
	mIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	mIndexBufferView.SizeInBytes = indicesBufferSize;
}

void D3D12RenderSystem::Render()
{
    // Prepare device resources
	auto commandAllocator = mDevice.mCommandAllocators[mCurrentFrame];
	auto renderTarget = mWindow->mRenderTargets[mCurrentFrame];
	auto commandList = mDevice.mCommandList;

	// Reset command allocator
	commandAllocator->Reset();

	// Get CommandList and reset
	commandList->Reset(commandAllocator.Get(), nullptr);

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

	commandList->RSSetViewports(1, &mWindow->mViewport);
	commandList->RSSetScissorRects(1, &mWindow->mScissorRect);

	 // Set pipeline
	commandList->SetGraphicsRootSignature(mRootSignature.Get());
	commandList->SetPipelineState(mPipelineState.Get());

	// //Set quad data
	//commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//commandList->IASetVertexBuffers(0, 1, &mVertexBufferView);
	// // Draw
	//commandList->DrawInstanced(6, 1, 0, 0);

	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->IASetVertexBuffers(0, 1, &mVertexBufferView);
	commandList->IASetIndexBuffer(&mIndexBufferView);
	commandList->DrawIndexedInstanced(mIndexCount, 1, 0, 0, 0);

	// Transition render target into correct state to present.
	{
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(renderTarget.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
		commandList->ResourceBarrier(1, &barrier);
	}

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
		mWindow->ChangeViewportSize(width, height);

		// Wait until all previous GPU work is complete.
		WaitForGpu();

		// Window Dependent Resources
		ResetFenceValues();
		// These resources need to be recreated every time the window size is changed.
		mWindow->CreateWindowSizeDependentResources(mDevice);
		mCurrentFrame = mWindow->mSwapChain->GetCurrentBackBufferIndex();
	}
}

// void D3D12RenderSystem::Tick()
// {
//     static uint64_t frameCounter = 0;
//     static double elapsedSeconds = 0.0;
//     static std::chrono::high_resolution_clock clock;
//     static auto t0 = clock.now();
 
//     frameCounter++;
//     auto t1 = clock.now();
//     auto deltaTime = t1 - t0;
//     t0 = t1;

// 	elapsedSeconds += deltaTime.count() * 1e-9;
//     if (elapsedSeconds > 1.0)
//     {
//         // char buffer[500];
//         // auto fps = frameCounter / elapsedSeconds;
//         // sprintf_s(buffer, 500, "FPS: %f\n", fps);
//         // OutputDebugString(buffer);
//         frameCounter = 0;
//         elapsedSeconds = 0.0;
//     }

// 	// Don't try render in first frame
// 	// if (m_frameCount == 0)
// 	// {
// 	// 	return;
// 	// }

// 	if (frameCounter != 0)
// 		Render();
// }

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

	CreateBuffers();
}

void D3D12RenderSystem::CreateDeviceDependentResources()
{
	// Create an empty root signature.
	{
		CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

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
