//
//  LucusMeshFormatManager.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 22/02/2020.
//

#include "LucusMeshFormatManager.h"

using namespace LucusEngine;

MeshFormatManager::MeshFormatManager()
{
    //
}

MeshFormatManager::~MeshFormatManager()
{
    MeshFormatIt It = mFormats.begin();
    for ( ; It != mFormats.end(); It++)
    {
        delete It->second;
    }
}

MeshFormat* MeshFormatManager::FindFormat( cc8* name )
{
    if (name)
    {
        u32 hash = Utils::HashName( name );
        auto search = mFormats.find( hash );
        return (search != mFormats.end()) ? mFormats[hash] : nullptr;
    }
    return nullptr;
}
