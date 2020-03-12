//
//  LucusD3D12RenderSystem.h
//  LucusGame
//
//  Created by Alexander Kardakov on 15/02/2020.
//

#ifndef _LUCUS_ENGINE_D3D12_RENDER_SYSTEM_H
#define _LUCUS_ENGINE_D3D12_RENDER_SYSTEM_H

#include "LucusD3D12Prerequisites.h"
#include "LucusRenderSystem.h"
#include "LucusD3D12Device.h"
#include "LucusD3D12Window.h"

// temp
// #include "LucusMesh.h"

namespace LucusEngine
{
    class D3D12RenderSystem: public RenderSystem
    {
    public:
        D3D12RenderSystem();
        virtual ~D3D12RenderSystem();

        virtual RenderWindow* CreateRenderWindow(u32 width, u32 height) override;
        virtual void CreateBuffers() override;
        virtual void Render() override;
        
        virtual void ChangeViewportSize(u32 width, u32 height) override;

        // void Tick();
        
        void WaitForGpu();
        void MoveToNextFrame();

        void CreateDevice();
        void CreateDeviceDependentResources();

        void ResetFenceValues();

        void SetCoreWindow(Windows::UI::Core::CoreWindow^ window);

    public:
        D3D12Device mDevice;

        D3D12Window* mWindow;
    
    private:
        Microsoft::WRL::ComPtr<ID3D12RootSignature>     mRootSignature;

        u32											    mCurrentFrame;

        //
        Microsoft::WRL::ComPtr<ID3D12PipelineState>     mPipelineState;

        std::vector<byte>								mVertexShader;
		std::vector<byte>								mPixelShader;

        // // CPU/GPU Synchronization.
		Microsoft::WRL::ComPtr<ID3D12Fence>				mFence;
		UINT64											mFenceValues[c_frameCount];
		HANDLE											mFenceEvent;

		bool											mReady;

        // // App resources.
	    // Microsoft::WRL::ComPtr<ID3D12Resource>          mVertexBuffer;
		// D3D12_VERTEX_BUFFER_VIEW                        mVertexBufferView;
		// Microsoft::WRL::ComPtr<ID3D12Resource>          mIndexBuffer;
		// D3D12_INDEX_BUFFER_VIEW							mIndexBufferView;
		// u32												mIndexCount;

		// App temp resources
		// bool mResourceCreated;
		// Mesh* mMesh;
	    
    };
}


#endif /* _LUCUS_ENGINE_D3D12_RENDER_SYSTEM_H */