//
//  LucusD3D12Device.h
//  LucusGame
//
//  Created by Alexander Kardakov on 15/02/2020.
//

#ifndef _LUCUS_ENGINE_D3D12_DEVICE_H
#define _LUCUS_ENGINE_D3D12_DEVICE_H

#include "LucusD3D12Prerequisites.h"

namespace LucusEngine
{
    class D3D12RenderSystem;

    struct D3D12Device
    {
        D3D12Device(D3D12RenderSystem* renderSystem);
        ~D3D12Device();

        void ReleaseAll();

        void Init();

        D3D_FEATURE_LEVEL                           mD3DMinFeatureLevel;

        D3D12RenderSystem*                          mRenderSystem;

        Microsoft::WRL::ComPtr<ID3D12Device>        mD3D12Device;
        Microsoft::WRL::ComPtr<IDXGIFactory4>		mDXGIFactory;

        Microsoft::WRL::ComPtr<ID3D12CommandQueue>  mCommandQueue;

        Microsoft::WRL::ComPtr<ID3D12CommandAllocator>	mCommandAllocators[c_frameCount];
        // Direct3D resources for cube geometry.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	mCommandList;

        // CPU/GPU Synchronization.
		Microsoft::WRL::ComPtr<ID3D12Fence>				mFence;
		UINT64											mFenceValues[c_frameCount];
		HANDLE											mFenceEvent;

        void GetAdapter(IDXGIAdapter1** ppAdapter);
        
    };
}

#endif /* _LUCUS_ENGINE_D3D12_DEVICE_H */