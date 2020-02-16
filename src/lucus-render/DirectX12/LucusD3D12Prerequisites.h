//
//  LucusD3D12Prerequisites.h
//  LucusGame
//
//  Created by Alexander Kardakov on 15/02/2020.
//

#ifndef _LUCUS_ENGINE_D3D12_PREREQUISITES_H
#define _LUCUS_ENGINE_D3D12_PREREQUISITES_H

#include <wrl.h>

#include <dxgi1_4.h>
#include <d3d12.h>
// #include <DirectXMath.h>
// #include <DirectXColors.h>

#include "d3dx12.h"

//  #ifdef _DEBUG
//  #include <dxgidebug.h>
//  #endif

#include <stdio.h>
#include <exception>

namespace DX
{
    // Helper class for COM exceptions
    class com_exception : public std::exception
    {
    public:
        com_exception(HRESULT hr) : result(hr) {}

        virtual const char* what() const override
        {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X", result);
            return s_str;
        }

    private:
        HRESULT result;
    };

    // Helper utility converts D3D API failures into exceptions.
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            throw com_exception(hr);
        }
    }
}

#endif /* _LUCUS_ENGINE_D3D12_PREREQUISITES_H */