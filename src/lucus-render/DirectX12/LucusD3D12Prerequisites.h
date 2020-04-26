//
//  LucusD3D12Prerequisites.h
//  LucusGame
//
//  Created by Alexander Kardakov on 15/02/2020.
//

#ifndef _LUCUS_ENGINE_D3D12_PREREQUISITES_H
#define _LUCUS_ENGINE_D3D12_PREREQUISITES_H

#include "LucusTypes.h"

#include <wrl.h>

#include <wchar.h>

using Microsoft::WRL::ComPtr;

#include <dxgi1_6.h>
#include <d3d12.h>
// #include <DirectXColors.h>

#include "d3dx12.h"

// #include <D3Dcompiler.h>

 #ifdef _DEBUG
 #include <dxgidebug.h>
 #endif

#include <memory>
#include <stdexcept>

#include <stdint.h>

#include <ppltasks.h>	// For create_task

// Use triple buffering.
// TODO: move from this
static const u32 c_frameCount = 3;

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

    // Function that reads from a binary file asynchronously.
	inline Concurrency::task<std::vector<byte>> ReadDataAsync(const std::wstring& filename)
	{
		using namespace Windows::Storage;
		using namespace Concurrency;

		auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;

		return create_task(folder->GetFileAsync(Platform::StringReference(filename.c_str()))).then([](StorageFile^ file)
		{
			return FileIO::ReadBufferAsync(file);
		}).then([](Streams::IBuffer^ fileBuffer) -> std::vector<byte>
		{
			std::vector<byte> returnBuffer;
			returnBuffer.resize(fileBuffer->Length);
			Streams::DataReader::FromBuffer(fileBuffer)->ReadBytes(Platform::ArrayReference<byte>(returnBuffer.data(), fileBuffer->Length));
			return returnBuffer;
		});
	}
}

#endif /* _LUCUS_ENGINE_D3D12_PREREQUISITES_H */