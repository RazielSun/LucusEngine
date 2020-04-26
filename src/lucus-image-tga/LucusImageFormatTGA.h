//
//  LucusImageFormatTGA.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 21/03/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#ifndef _LUCUS_ENGINE_IMAGE_FORMAT_TGA_H
#define _LUCUS_ENGINE_IMAGE_FORMAT_TGA_H

#include "LucusImageFormat.h"

namespace LucusEngine
{
    //typedef struct __attribute__ ((packed)) TGAHeader
    //{
    //    uint8_t  IDSize;         // Size of ID info following header
    //    uint8_t  colorMapType;   // Whether this is a paletted image
    //    uint8_t  imageType;      // type of image 0=none, 1=indexed, 2=rgb, 3=grey, +8=rle packed
    //
    //    int16_t  colorMapStart;  // Offset to color map in palette
    //    int16_t  colorMapLength; // Number of colors in palette
    //    uint8_t  colorMapBpp;    // Number of bits per palette entry
    //
    //    uint16_t xOrigin;        // X Origin pixel of lower left corner if tile of larger image
    //    uint16_t yOrigin;        // Y Origin pixel of lower left corner if tile of larger image
    //    uint16_t width;          // Width in pixels
    //    uint16_t height;         // Height in pixels
    //    uint8_t  bitsPerPixel;   // Bits per pixel 8,16,24,32
    //    union {
    //        struct
    //        {
    //            uint8_t bitsPerAlpha : 4;
    //            uint8_t topOrigin    : 1;
    //            uint8_t rightOrigin  : 1;
    //            uint8_t reserved     : 2;
    //        };
    //        uint8_t descriptor;
    //    };
    //} TGAHeader;

    typedef struct TGAHeader
    {
        char IDSize;
        char colorMapType;
        char imageType;

        short int colorMapStart;
        short int colorMapLength;
        char colorMapBpp;

        short int xOrigin;
        short int yOrigin;
        short int width;
        short int height;
        char bitsPerPixel;
        char descriptor;
    } TGAHeader;

    class Image;

    class ImageFormatTGA : public ImageFormat
    {
    private:
        char* srcPixelData;
        char* colorMapPixelData;
        char* dstPixelData;
        
        std::ifstream mStream;
        
    public:
        ImageFormatTGA();
        virtual ~ImageFormatTGA();
        
        bool OpenFile(cc8* path);
        virtual void LoadImage(Image* image, cc8* name) override;
    };
}



#endif /* _LUCUS_ENGINE_IMAGE_FORMAT_TGA_H */
