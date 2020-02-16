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
    static const u32 c_frameCount = 3;		// Use triple buffering.

    class D3D12RenderSystem: public RenderSystem
    {
    public:
        D3D12RenderSystem();
        virtual ~D3D12RenderSystem();

        virtual RenderWindow* CreateRenderWindow(u32 width, u32 height) override;
        virtual void CreateBuffers() override;
        virtual void Render() override;
        
        virtual void ChangeViewportSize(u32 width, u32 height) override;

        void Tick();
        
        void WaitForGpu();
        void MoveToNextFrame();

        void CreateDeviceResources();
        void CreateWindowSizeDependentResources();
        void SetCoreWindow(Windows::UI::Core::CoreWindow^ window);

    public:
        D3D12Device mDevice;

        D3D12Window* mWindow;
    
    private:
        void GetAdapter(IDXGIAdapter1** ppAdapter);

        u32											    m_currentFrame;

        // Direct3D objects.
        Microsoft::WRL::ComPtr<ID3D12Device>            m_d3dDevice;
        Microsoft::WRL::ComPtr<IDXGIFactory4>			m_dxgiFactory;
        Microsoft::WRL::ComPtr<IDXGISwapChain3>			m_swapChain;
		Microsoft::WRL::ComPtr<ID3D12Resource>			m_renderTargets[c_frameCount];
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	m_rtvHeap;
        Microsoft::WRL::ComPtr<ID3D12CommandQueue>      m_commandQueue;
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator>	m_commandAllocators[c_frameCount];

        // Direct3D resources for cube geometry.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	m_commandList;

        // CPU/GPU Synchronization.
		Microsoft::WRL::ComPtr<ID3D12Fence>				m_fence;
		UINT64											m_fenceValues[c_frameCount];
		HANDLE											m_fenceEvent;

        D3D_FEATURE_LEVEL                               m_d3dMinFeatureLevel;
        u32											    m_rtvDescriptorSize;
    };
}


#endif /* _LUCUS_ENGINE_D3D12_RENDER_SYSTEM_H */