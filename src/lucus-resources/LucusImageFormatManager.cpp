//
//  LucusImageFormatManager.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 21/03/2020.
//

#include "LucusImageFormatManager.h"

using namespace LucusEngine;

ImageFormatManager::ImageFormatManager()
{
    //
}

ImageFormatManager::~ImageFormatManager()
{
    ImageFormatIt It = mFormats.begin();
    for ( ; It != mFormats.end(); It++)
    {
        delete It->second;
    }
}

ImageFormat* ImageFormatManager::FindFormat( cc8* name )
{
    if (name)
    {
        u32 hash = Utils::HashName( name );
        auto search = mFormats.find( hash );
        return (search != mFormats.end()) ? mFormats[hash] : nullptr;
    }
    return nullptr;
}
