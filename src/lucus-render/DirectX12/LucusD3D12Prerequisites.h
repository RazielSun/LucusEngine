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

using Microsoft::WRL::ComPtr;

#include <dxgi1_4.h>
#include <d3d12.h>
// #include <DirectXColors.h>

#include "d3dx12.h"

// #include <D3Dcompiler.h>

 #ifdef _DEBUG
 #include <dxgidebug.h>
 #endif

#include <algorithm>
#include <exception>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

#include <stdio.h>

#include <stdint.h>

#include <ppltasks.h>	// For create_task

// Use triple buffering.
// TODO: move from this
static const u32 c_frameCount = 3;	


#include <DirectXMath.h>
// TODO: move from this
typedef struct {
    DirectX::XMFLOAT2 position;
    DirectX::XMFLOAT4 color;
} DefaultVertex;

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

     inline std::vector<uint8_t> ReadData(_In_z_ const wchar_t* name)
     {
         std::ifstream inFile(name, std::ios::in | std::ios::binary | std::ios::ate);

 #if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
         if (!inFile)
         {
             wchar_t moduleName[_MAX_PATH];
             if (!GetModuleFileNameW(nullptr, moduleName, _MAX_PATH))
                 throw std::exception("GetModuleFileName");

             wchar_t drive[_MAX_DRIVE];
             wchar_t path[_MAX_PATH];

             if (_wsplitpath_s(moduleName, drive, _MAX_DRIVE, path, _MAX_PATH, nullptr, 0, nullptr, 0))
                 throw std::exception("_wsplitpath_s");

             wchar_t filename[_MAX_PATH];
             if (_wmakepath_s(filename, _MAX_PATH, drive, path, name, nullptr))
                 throw std::exception("_wmakepath_s");

             inFile.open(filename, std::ios::in | std::ios::binary | std::ios::ate);
         }
 #endif

         if (!inFile)
             throw std::exception("ReadData");

         std::streampos len = inFile.tellg();
         if (!inFile)
             throw std::exception("ReadData");

         std::vector<uint8_t> blob;
         blob.resize(size_t(len));

         inFile.seekg(0, std::ios::beg);
         if (!inFile)
             throw std::exception("ReadData");

         inFile.read(reinterpret_cast<char*>(blob.data()), len);
         if (!inFile)
             throw std::exception("ReadData");

         inFile.close();

         return blob;
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