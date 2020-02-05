//
// pch.h
//

#pragma once

// Use the C++ standard templated min/max
#define NOMINMAX

#include <wrl.h>

#include <dxgi1_4.h>
#include <d3d12.h>
// #include <DirectXMath.h>
// #include <DirectXColors.h>

#include "d3dx12.h"

#include <algorithm>
#include <memory> // for shared_ptr and etc
// #include <stdexcept> // out_of_range
#include <chrono> // for time
#include <agile.h>

//  #ifdef _DEBUG
//  #include <dxgidebug.h>
//  #endif

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