//
//  LucusD3D12ComponentProxy.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 10/03/2020.
//

#include "LucusD3D12ComponentProxy.h"
#include "LucusTransform.h"
#include "LucusMesh.h"
#include "LucusImage.h"
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

	mMappedDataAddress = nullptr;
}

void D3D12ComponentProxy::CreateBuffers(Mesh* mesh)
{
	CreateBuffers(mesh, mOwnerDevice->mCommandList);
}

void D3D12ComponentProxy::CreateBuffers(Mesh* mesh, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)
{
    if (nullptr != mesh)
    {
        // Create the buffers.
        std::vector<SimpleVertex>* vertices = mesh->GetVertices();

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
            vertexData.pData = reinterpret_cast<BYTE*>(vertices->data());
            vertexData.RowPitch = mVertexBufferSize;
            vertexData.SlicePitch = vertexData.RowPitch;

            UpdateSubresources(commandList.Get(), mVertexBuffer.Get(), mVertexBufferUpload.Get(), 0, 0, 1, &vertexData);
            commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mVertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));

			//commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mVertexBuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
			//UpdateSubresources<1>(commandList.Get(), mVertexBuffer.Get(), vertexBufferUpload.Get(), 0, 0, 1, &vertexData);
			//commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mVertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
        }

        std::vector<TriangleIndex>* indices = mesh->GetIndices();

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
            indexData.pData = reinterpret_cast<BYTE*>(indices->data());
            indexData.RowPitch = mIndicesBufferSize;
            indexData.SlicePitch = indexData.RowPitch;

            UpdateSubresources(commandList.Get(), mIndexBuffer.Get(), mIndicesBufferUpload.Get(), 0, 0, 1, &indexData);
            commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mIndexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER));

			//mOwnerDevice->mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mIndexBuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
			//UpdateSubresources<1>(mOwnerDevice->mCommandList.Get(), mIndexBuffer.Get(), indicesBufferUpload.Get(), 0, 0, 1, &indexData);
			//mOwnerDevice->mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mIndexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
        }

		// Create constant buffer

		const u32 constantBufferSize = sizeof(Uniforms);
		CD3DX12_RESOURCE_DESC constantBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(constantBufferSize);

		ThrowIfFailed(mOwnerDevice->mD3D12Device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&constantBufferDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&mConstantBuffer)));

		// Map the constant buffers.
		//ZeroMemory(&mMappedDataAddress, sizeof(mMappedDataAddress));
		ThrowIfFailed(mConstantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&mMappedDataAddress)));

		// We do not need to unmap until we are done with the resource.  However, we must not write to
		// the resource while it is in use by the GPU (so we must use synchronization techniques).
		//	CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
		//	ThrowIfFailed(mConstantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&mMappedData)));

		mBuffersLoaded = true;
    }
}

void D3D12ComponentProxy::CreateTexture(Image* image)
{
    CreateTexture(image, mOwnerDevice->mCommandList);
}

void D3D12ComponentProxy::CreateTexture(Image* image, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)
{
    if (nullptr != image)
    {
        // Create texture.
        D3D12_RESOURCE_DESC txtDesc = {};
        txtDesc.MipLevels = txtDesc.DepthOrArraySize = 1;
        txtDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        txtDesc.SampleDesc.Count = 1;
        txtDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        txtDesc.Width = image->GetWidth();
        txtDesc.Height = image->GetHeight();

        CD3DX12_HEAP_PROPERTIES defaultHeapProperties(D3D12_HEAP_TYPE_DEFAULT);
        ThrowIfFailed(mOwnerDevice->mD3D12Device->CreateCommittedResource(
                &defaultHeapProperties,
                D3D12_HEAP_FLAG_NONE,
                &txtDesc,
                D3D12_RESOURCE_STATE_COPY_DEST,
                nullptr,
                IID_PPV_ARGS(&mTexture)));

        const UINT64 uploadBufferSize = GetRequiredIntermediateSize(mTexture.Get(), 0, 1);

        // Create the GPU upload buffer.
        auto resDesc = CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize);

        CD3DX12_HEAP_PROPERTIES uploadHeapProperties(D3D12_HEAP_TYPE_UPLOAD);
        ThrowIfFailed(mOwnerDevice->mD3D12Device->CreateCommittedResource(
                &uploadHeapProperties,
                D3D12_HEAP_FLAG_NONE,
                &resDesc,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&mTextureUpload)));

        D3D12_SUBRESOURCE_DATA textureData = {};
        textureData.pData = image->GetBitmap();
        textureData.RowPitch = static_cast<LONG_PTR>(txtDesc.Width * sizeof(uint32_t));
        textureData.SlicePitch = txtDesc.Width * txtDesc.Height;

        UpdateSubresources(commandList.Get(), mTexture.Get(), mTextureUpload.Get(), 0, 0, 1, &textureData);

        auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(mTexture.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
        commandList->ResourceBarrier(1, &barrier);
    }
}

void D3D12ComponentProxy::UpdateUniforms(const Uniforms& uniforms, const Transform& transform)
{
	Uniforms cUniforms;
	memcpy(&cUniforms, &uniforms, sizeof(Uniforms));
    
     cUniforms.MODEL_MATRIX = transform.GetModelMatrix().GetNative(); //XMMatrixMultiply
	 // Need to be stored as CMXMatrix? or we can use our matrices and store data
	 DirectX::XMMATRIX model = DirectX::XMLoadFloat4x4((const DirectX::XMFLOAT4X4*)(&cUniforms.MODEL_MATRIX));
	 DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4((const DirectX::XMFLOAT4X4*)(&cUniforms.VIEW_MATRIX));
	 DirectX::XMMATRIX projection = DirectX::XMLoadFloat4x4((const DirectX::XMFLOAT4X4*)(&cUniforms.PROJ_MATRIX));
	 DirectX::XMMATRIX result = DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(projection, view), model);
	 DirectX::XMStoreFloat4x4((&cUniforms.MVP_MATRIX), result);

    // Update constant buffer data
	memcpy(mMappedDataAddress, &cUniforms, sizeof(cUniforms));
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
