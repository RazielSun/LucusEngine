//
//  LucusD3D12ComponentProxy.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 10/03/2020.
//

#ifndef _LUCUS_ENGINE_D3D12_COMPONENT_PROXY_H
#define _LUCUS_ENGINE_D3D12_COMPONENT_PROXY_H

#include "LucusD3D12Prerequisites.h"
#include "LucusSceneComponentProxy.h"

namespace LucusEngine
{
    class Mesh;
    class Transform;

	struct D3D12Device;
    
    class D3D12ComponentProxy : public SceneComponentProxy
    {
    public:
        D3D12ComponentProxy(D3D12Device* ownerDevice);
        ~D3D12ComponentProxy();
        
        virtual void CreateBuffers(Mesh* mesh) override;
		virtual void CreateTexture(Image* image) override;
        virtual void UpdateUniforms(const Uniforms& uniforms, SceneComponent* component) override;
        
		void CreateBuffers(Mesh* mesh, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);
        void CreateTexture(Image* image, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);
        void DrawIndexed(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);
        void SetupBufferViews();

	public:
		Microsoft::WRL::ComPtr<ID3D12Resource>          mConstantBuffer = nullptr;
		u8*												mMappedDataAddress = nullptr;

        Microsoft::WRL::ComPtr<ID3D12Resource>          mTexture = nullptr;
        Microsoft::WRL::ComPtr<ID3D12Resource>			mTextureUpload = nullptr;
        
    protected:
        D3D12Device* mOwnerDevice;

        // App resources.
	    Microsoft::WRL::ComPtr<ID3D12Resource>          mVertexBuffer = nullptr;
		D3D12_VERTEX_BUFFER_VIEW                        mVertexBufferView;
        u32                                             mVertexBufferSize;
		Microsoft::WRL::ComPtr<ID3D12Resource>			mVertexBufferUpload = nullptr;

		Microsoft::WRL::ComPtr<ID3D12Resource>          mIndexBuffer = nullptr;
		D3D12_INDEX_BUFFER_VIEW							mIndexBufferView;
        u32                                             mIndicesBufferSize;
		u32												mIndexCount;
		Microsoft::WRL::ComPtr<ID3D12Resource>			mIndicesBufferUpload = nullptr;

		bool											mBuffersLoaded;
		bool											mReadyToDraw;
    };
}

#endif /* _LUCUS_ENGINE_D3D12_COMPONENT_PROXY_H */
