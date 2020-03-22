//
//  LucusImageFormatManager.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 21/03/2020.
//

#ifndef _LUCUS_ENGINE_IMAGE_FORMAT_MANAGER_H
#define _LUCUS_ENGINE_IMAGE_FORMAT_MANAGER_H

#include "LucusTypes.h"
#include "LucusUtils.h"
#include "LucusImageFormat.h"
#include <unordered_map>

namespace LucusEngine
{
    typedef std::unordered_map<u32, ImageFormat*> MapImageFormats;
    typedef MapImageFormats::iterator ImageFormatIt;
    
    class ImageFormatManager
    {
        MapImageFormats mFormats;
        
    public:
        ImageFormatManager();
        ~ImageFormatManager();
        
        ImageFormat* FindFormat( cc8* name );
        
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

#endif /* _LUCUS_ENGINE_IMAGE_FORMAT_MANAGER_H */
