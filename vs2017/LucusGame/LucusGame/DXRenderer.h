
#pragma once

namespace DX
{
    static const UINT c_frameCount = 3;		// Use triple buffering.

    class DXRenderer
    {
    public:
        DXRenderer();
        ~DXRenderer();

        void Tick();
        
        void WaitForGpu();
        void MoveToNextFrame();

        void CreateDeviceResources();
        void CreateWindowSizeDependentResources();
        void SetWindow(Windows::UI::Core::CoreWindow^ window);
    private:
        void Render();

        void GetAdapter(IDXGIAdapter1** ppAdapter);

        UINT											m_currentFrame;

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

        // Cached reference to the Window.
		Platform::Agile<Windows::UI::Core::CoreWindow>	m_window;
        D3D_FEATURE_LEVEL                               m_d3dMinFeatureLevel;
        UINT											m_rtvDescriptorSize;
    };
}