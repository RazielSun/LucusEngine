//
//  LucusFileSystem.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 21/02/2020.
//

#ifndef _LUCUS_ENGINE_FILESYSTEM_H
#define _LUCUS_ENGINE_FILESYSTEM_H

#include "LucusTypes.h"
#include <vector>
#include <string>

namespace LucusEngine
{
    class FileSystem
    {
    public:
        FileSystem();
        ~FileSystem();
        
    public:
        void ChangeWorkingDir(char const* path);
        
        std::vector<cc8> ReadData() noexcept(false);
//        void ReadDataAsync();
    protected:
        std::string mWorkingDir;
    };
}

#endif /* _LUCUS_ENGINE_FILESYSTEM_H */
