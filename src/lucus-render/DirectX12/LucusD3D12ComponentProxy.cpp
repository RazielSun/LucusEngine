//
//  LucusD3D12ComponentProxy.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 10/03/2020.
//

#include "LucusD3D12ComponentProxy.h"
#include "LucusTransform.h"
#include "LucusMesh.h"
#include "LucusD3D12Device.h"

#include <wchar.h>

using namespace DX;

using namespace LucusEngine;

D3D12ComponentProxy::D3D12ComponentProxy(D3D12Device* ownerDevice) :
	mOwnerDevice(ownerDevice),
	mBuffersLoaded(false),
	mReadyToDraw(false)
{
    //
}

D3D12ComponentProxy::~D3D12ComponentProxy()
{
    mOwnerDevice = nullptr;

	if (mConstantBuffer != nullptr)
		mConstantBuffer->Unmap(0, nullptr);

	mMappedData = nullptr;
}

// const VectorVertices* vertices = mesh->GetVertices();
		// NSUInteger verticesLength = vertices->size() * sizeof(SimpleVertex); // bytes
		// mVerticesBuf = [mOwnerDevice->mDevice newBufferWithBytes:vertices->data() length:verticesLength options:MTLResourceOptionCPUCacheModeDefault];

		// const VectorIndices* indices = mesh->GetIndices();
		// NSUInteger indicesLength = indices->size() * sizeof(TriangleIndex); // bytes
		// mIndicesBuf = [mOwnerDevice->mDevice newBufferWithBytes:indices->data() length:indicesLength options:MTLResourceOptionCPUCacheModeDefault];

		// mIndicesCount = indicesLength / sizeof(u32); // indices count

		// mUniforms = [mOwnerDevice->mDevice newBufferWithLength:sizeof(Uniforms) options:MTLResourceStorageModeShared];

		// mMesh = new Mesh();
		// mMesh->Load("meshes/cube.fbx");

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

void D3D12ComponentProxy::CreateBuffers(const Mesh* mesh)
{
	CreateBuffers(mesh, mOwnerDevice->mCommandList);
}

void D3D12ComponentProxy::CreateBuffers(const Mesh* mesh, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)
{
    if (nullptr != mesh)
    {
        // Create the buffers.
        const std::vector<SimpleVertex>* vertices = mesh->GetVertices();

        mVertexBufferSize = static_cast<u32>(vertices->size() * sizeof(SimpleVertex));// sizeof(quad);

        // Create the vertex buffer resource in the GPU's default heap and copy vertex data into it using the upload heap.
        // The upload resource must not be released until after the GPU has finished using it.
        //Microsoft::WRL::ComPtr<ID3D12Resource> vertexBufferUpload;

        CD3DX12_RESOURCE_DESC vertexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(mVertexBufferSize);

        CD3DX12_HEAP_PROPERTIES defaultHeapProperties(D3D12_HEAP_TYPE_DEFAULT);
        ThrowIfFailed(mOwnerDevice->mD3D12Device->CreateCommittedResource(
            &defaultHeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &vertexBufferDesc,
            D3D12_RESOURCE_STATE_COPY_DEST,
            nullptr,
            IID_PPV_ARGS(&mVertexBuffer)));

        CD3DX12_HEAP_PROPERTIES uploadHeapProperties(D3D12_HEAP_TYPE_UPLOAD);
        ThrowIfFailed(mOwnerDevice->mD3D12Device->CreateCommittedResource(
            &uploadHeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &vertexBufferDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&mVertexBufferUpload)));

        mVertexBuffer->SetName(L"Vertex Buffer");
		mVertexBufferUpload->SetName(L"Vertex Buffer Upload");
		

        // Upload the vertex buffer to the GPU.
        {
            D3D12_SUBRESOURCE_DATA vertexData = {};
            vertexData.pData = reinterpret_cast<BYTE*>(const_cast<std::vector<SimpleVertex>*>(vertices)->data());
            vertexData.RowPitch = mVertexBufferSize;
            vertexData.SlicePitch = vertexData.RowPitch;

            UpdateSubresources(commandList.Get(), mVertexBuffer.Get(), mVertexBufferUpload.Get(), 0, 0, 1, &vertexData);
            commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mVertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));

			//commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mVertexBuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
			//UpdateSubresources<1>(commandList.Get(), mVertexBuffer.Get(), vertexBufferUpload.Get(), 0, 0, 1, &vertexData);
			//commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mVertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
        }

        const std::vector<TriangleIndex>* indices = mesh->GetIndices();

        mIndicesBufferSize = static_cast<u32>(indices->size() * sizeof(TriangleIndex));
        mIndexCount = mIndicesBufferSize / sizeof(u32);

        //Microsoft::WRL::ComPtr<ID3D12Resource> indicesBufferUpload;

        CD3DX12_RESOURCE_DESC indexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(mIndicesBufferSize);

        ThrowIfFailed(mOwnerDevice->mD3D12Device->CreateCommittedResource(
            &defaultHeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &indexBufferDesc,
            D3D12_RESOURCE_STATE_COPY_DEST,
            nullptr,
            IID_PPV_ARGS(&mIndexBuffer)));

        ThrowIfFailed(mOwnerDevice->mD3D12Device->CreateCommittedResource(
            &uploadHeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &indexBufferDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&mIndicesBufferUpload)));

        mIndexBuffer->SetName(L"Index Buffer");
		mIndicesBufferUpload->SetName(L"Index Buffer Upload");

        // Upload the index buffer to the GPU.
        {
            D3D12_SUBRESOURCE_DATA indexData = {};
            indexData.pData = reinterpret_cast<BYTE*>(const_cast<std::vector<TriangleIndex>*>(indices)->data());
            indexData.RowPitch = mIndicesBufferSize;
            indexData.SlicePitch = indexData.RowPitch;

            UpdateSubresources(commandList.Get(), mIndexBuffer.Get(), mIndicesBufferUpload.Get(), 0, 0, 1, &indexData);
            commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mIndexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER));

			//mOwnerDevice->mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mIndexBuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
			//UpdateSubresources<1>(mOwnerDevice->mCommandList.Get(), mIndexBuffer.Get(), indicesBufferUpload.Get(), 0, 0, 1, &indexData);
			//mOwnerDevice->mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mIndexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
        }

        // Create constant buffer

		//const u32 constantBufferSize = sizeof(Uniforms);

		//CD3DX12_RESOURCE_DESC constantBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(constantBufferSize);

		//ThrowIfFailed(mOwnerDevice->mD3D12Device->CreateCommittedResource(
		//	&uploadHeapProperties,
		//	D3D12_HEAP_FLAG_NONE,
		//	&constantBufferDesc,
		//	D3D12_RESOURCE_STATE_GENERIC_READ,
		//	nullptr,
		//	IID_PPV_ARGS(&mConstantBuffer)));

		//{
		//	// Map the constant buffers.
		//	CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
		//	ThrowIfFailed(mConstantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&mMappedData)));

		//	// We do not need to unmap until we are done with the resource.  However, we must not write to
		//	// the resource while it is in use by the GPU (so we must use synchronization techniques).
		//}

		mBuffersLoaded = true;
    }
}

void D3D12ComponentProxy::UpdateUniforms(const Uniforms& uniforms, const Transform& transform)
{
	//Uniforms cUniforms;
	//memcpy(&cUniforms, &uniforms, sizeof(Uniforms));
 //   
 //    cUniforms.MODEL_MATRIX = transform.GetModelMatrix().GetNative();
 //    //cUniforms.MVP_MATRIX = matrix_multiply(cUniforms->PROJ_MATRIX, matrix_multiply(cUniforms->VIEW_MATRIX, cUniforms->MODEL_MATRIX));

 //   // Update constant buffer data
	//memcpy(mMappedData, &cUniforms, sizeof(cUniforms));
}

void D3D12ComponentProxy::DrawIndexed(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	commandList)
{
	if (!mReadyToDraw && mBuffersLoaded)
	{
		mReadyToDraw = true;
		SetupBufferViews();
	}

	// Set Constant Buffer
	//auto cbGpuAddress = mConstantBuffer->GetGPUVirtualAddress();
	//commandList->SetComputeRootConstantBufferView(GlobalRootSignatureParams::SceneConstantSlot, cbGpuAddress);
    
	// Set Index And Vertex Buffers
    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->IASetVertexBuffers(0, 1, &mVertexBufferView);
	commandList->IASetIndexBuffer(&mIndexBufferView);

	// Draw
	commandList->DrawIndexedInstanced(mIndexCount, 1, 0, 0, 0);
}

void D3D12ComponentProxy::SetupBufferViews()
{
    mVertexBufferView.BufferLocation = mVertexBuffer->GetGPUVirtualAddress();
	mVertexBufferView.StrideInBytes = sizeof(SimpleVertex);
	mVertexBufferView.SizeInBytes = mVertexBufferSize;

	mIndexBufferView.BufferLocation = mIndexBuffer->GetGPUVirtualAddress();
	mIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	mIndexBufferView.SizeInBytes = mIndicesBufferSize;
}
