//
//  LucusImageFormat.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 21/03/2020.
//

#ifndef _LUCUS_ENGINE_IMAGE_FORMAT_H
#define _LUCUS_ENGINE_IMAGE_FORMAT_H

#include "LucusTypes.h"

namespace LucusEngine
{
    class Image;

    class ImageFormat
    {
    public:
        ImageFormat();
        virtual ~ImageFormat();
        
        virtual void LoadImage(Image* image, cc8* name) = 0;
    };
}

#endif /* _LUCUS_ENGINE_IMAGE_FORMAT_H */
