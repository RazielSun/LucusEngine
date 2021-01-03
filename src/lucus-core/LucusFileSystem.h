//
//  LucusFileSystem.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 21/02/2020.
//

#ifndef _LUCUS_ENGINE_FILESYSTEM_H
#define _LUCUS_ENGINE_FILESYSTEM_H

#include "LucusTypes.h"

namespace LucusEngine
{
    class FileSystem
    {
    public:
        FileSystem();
        ~FileSystem();
        
    public:
        void ChangeWorkingDir(char const* path);
        
        std::string GetAssetPath( cc8* name );
        std::string GetAssetPath( cc8* folder, cc8* name );

        std::string GetScriptPath( cc8* name );
        std::string GetMeshPath( cc8* name );
        std::string GetTexturePath( cc8* name );
        
        std::string GetFileFormat( cc8* name );
        
        std::vector<u8> ReadData( cc8* name ) noexcept(false);
//        void ReadDataAsync();
    protected:
        std::string mWorkingDir;
    };
}

#endif /* _LUCUS_ENGINE_FILESYSTEM_H */
