//
//  LucusImage.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 21/03/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#ifndef _LUCUS_ENGINE_IMAGE_H
#define _LUCUS_ENGINE_IMAGE_H

#include "LucusTypes.h"
#include "LucusResource.h"
#include "LucusPtr.h"

namespace LucusEngine
{
    class Image : public Resource
    {
    protected:
        u32 mWidth;
        u32 mHeight;
        void* mBitmap;
        
    public:
        Image();
        virtual ~Image();
        
        Image(u32 width, u32 height, char* pixelData, u32 pixelDataSize);
        
        void Load( cc8* name );
        void Load(u32 width, u32 height, char* pixelData, u32 pixelDataSize);
        void Load24(u32 width, u32 height, char* pixelData, u32 pixelDataSize);
        void LoadIndexed(u32 width, u32 height, char* indexes, u32* pallete, u32 palleteSize);
        
    public:
        u32 GetWidth() { return mWidth; }
        u32 GetHeight() { return mHeight; }
        void* GetBitmap() { return mBitmap; }
        
    protected:
        void ReadData(char* pixelData, u32 pixelDataSize);
    };

    typedef Ptr<Image> ImagePtr;
}

#endif /* _LUCUS_ENGINE_IMAGE_H */
