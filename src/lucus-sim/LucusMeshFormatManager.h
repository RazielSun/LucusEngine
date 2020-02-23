//
//  LucusMeshFormatManager.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 22/02/2020.
//

#ifndef _LUCUS_ENGINE_MESH_FORMAT_MANAGER_H
#define _LUCUS_ENGINE_MESH_FORMAT_MANAGER_H

#include "LucusTypes.h"
#include "LucusUtils.h"
#include "LucusMeshFormat.h"
#include <unordered_map>

namespace LucusEngine
{
    typedef std::unordered_map<u32, MeshFormat*> MapMeshFormats;
    typedef MapMeshFormats::iterator MeshFormatIt;
    
    class MeshFormatManager
    {
        MapMeshFormats mFormats;
        
    public:
        MeshFormatManager();
        ~MeshFormatManager();
        
        MeshFormat* FindFormat( cc8* name );
        
        template <class T>
        void RegisterFormat( cc8* name )
        {
            u32 hash = Utils::HashName( name );
            
            auto search = mFormats.find( hash );
            if (search != mFormats.end())
            {
                delete mFormats[hash];
                mFormats[hash] = nullptr;
            }
            mFormats[hash] = new T();
        }
    };
}

#endif /* _LUCUS_ENGINE_MESH_FORMAT_MANAGER_H */
