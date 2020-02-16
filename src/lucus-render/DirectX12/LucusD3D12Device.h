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

        D3D12RenderSystem* mRenderSystem;
    };
}

#endif /* _LUCUS_ENGINE_D3D12_DEVICE_H */