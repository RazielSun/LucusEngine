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

namespace LucusEngine
{
    class D3D12RenderSystem: public RenderSystem
    {
    public:
        D3D12RenderSystem();
        virtual ~D3D12RenderSystem();

        virtual RenderWindow* CreateRenderWindow(u32 width, u32 height) override;
        virtual void CreateBuffers() override;

        virtual void PreRender() override;
        virtual void Render() const override;
        
        virtual void ChangeViewportSize(u32 width, u32 height) override;

        // void Tick();
        
        void WaitForGpu();
        void MoveToNextFrame() const;

        void CreateDevice();
        void CreateDeviceDependentResources();

        void ResetFenceValues();

        void SetCoreWindow(Windows::UI::Core::CoreWindow^ window);

    public:
        D3D12Device mDevice;

        D3D12Window* mWindow;
    
    private:
        Microsoft::WRL::ComPtr<ID3D12RootSignature>     mRootSignature;

        mutable u32									    mCurrentFrame;

        //
        Microsoft::WRL::ComPtr<ID3D12PipelineState>     mPipelineState;

		// Descriptors
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	mDescriptorCBHeap;
		u32												mDescriptorCBSize;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	mDescriptorSRHeap;
		u32												mDescriptorSRSize;

        std::vector<byte>								mVertexShader;
		std::vector<byte>								mPixelShader;

        // // CPU/GPU Synchronization.
		Microsoft::WRL::ComPtr<ID3D12Fence>				mFence;
		mutable UINT64									mFenceValues[c_frameCount];
		HANDLE											mFenceEvent;

		bool											mReady;
	    
    };
}


#endif /* _LUCUS_ENGINE_D3D12_RENDER_SYSTEM_H */