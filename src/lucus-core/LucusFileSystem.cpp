//
//  LucusFileSystem.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 21/02/2020.
//

#include "LucusFileSystem.h"
#include <fstream>

using namespace LucusEngine;

FileSystem::FileSystem()
{
    //
}

FileSystem::~FileSystem()
{
    //
}

void FileSystem::ChangeWorkingDir(char const* path)
{
    if (path)
    {
        std::string buffer;
        buffer.append(path);
        if (buffer[buffer.length() - 1] != '/')
        {
            buffer.push_back('/');
        }
        mWorkingDir = buffer;
    }
}

std::string FileSystem::GetAssetPath( cc8* name )
{
    std::string fullPath;
    
    if (name)
    {
        fullPath.append(mWorkingDir);
        fullPath.append(name);
    }
    
    return fullPath;
}

std::string FileSystem::GetFileFormat( cc8* name )
{
    std::string path(name);
    size_t dotIndex = path.find_last_of('.');
    if (dotIndex != std::string::npos)
    {
        std::string format = path.substr( dotIndex + 1 );
//        std::transform( format.begin(), format.end(), format.begin(), ::tolower );
        return format;
    }
    return "";
}
    
std::vector<cc8> FileSystem::ReadData()
{
    std::vector<cc8> vec;
    
    return vec;
}

//inline std::vector<uint8_t> ReadData(_In_z_ const wchar_t* name)
//    {
//        std::ifstream inFile(name, std::ios::in | std::ios::binary | std::ios::ate);
//
//#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
//        if (!inFile)
//        {
//            wchar_t moduleName[_MAX_PATH];
//            if (!GetModuleFileNameW(nullptr, moduleName, _MAX_PATH))
//                throw std::exception("GetModuleFileName");
//
//            wchar_t drive[_MAX_DRIVE];
//            wchar_t path[_MAX_PATH];
//
//            if (_wsplitpath_s(moduleName, drive, _MAX_DRIVE, path, _MAX_PATH, nullptr, 0, nullptr, 0))
//                throw std::exception("_wsplitpath_s");
//
//            wchar_t filename[_MAX_PATH];
//            if (_wmakepath_s(filename, _MAX_PATH, drive, path, name, nullptr))
//                throw std::exception("_wmakepath_s");
//
//            inFile.open(filename, std::ios::in | std::ios::binary | std::ios::ate);
//        }
//#endif
//
//        if (!inFile)
//            throw std::exception("ReadData");
//
//        std::streampos len = inFile.tellg();
//        if (!inFile)
//            throw std::exception("ReadData");
//
//        std::vector<uint8_t> blob;
//        blob.resize(size_t(len));
//
//        inFile.seekg(0, std::ios::beg);
//        if (!inFile)
//            throw std::exception("ReadData");
//
//        inFile.read(reinterpret_cast<char*>(blob.data()), len);
//        if (!inFile)
//            throw std::exception("ReadData");
//
//        inFile.close();
//
//        return blob;
//    }
//
//   // Function that reads from a binary file asynchronously.
//   inline Concurrency::task<std::vector<byte>> ReadDataAsync(const std::wstring& filename)
//   {
//       using namespace Windows::Storage;
//       using namespace Concurrency;
//
//       auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;
//
//       return create_task(folder->GetFileAsync(Platform::StringReference(filename.c_str()))).then([](StorageFile^ file)
//       {
//           return FileIO::ReadBufferAsync(file);
//       }).then([](Streams::IBuffer^ fileBuffer) -> std::vector<byte>
//       {
//           std::vector<byte> returnBuffer;
//           returnBuffer.resize(fileBuffer->Length);
//           Streams::DataReader::FromBuffer(fileBuffer)->ReadBytes(Platform::ArrayReference<byte>(returnBuffer.data(), fileBuffer->Length));
//           return returnBuffer;
//       });
//   }
