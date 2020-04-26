//
//  LucusImageFormatPNG.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 21/03/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#include "LucusImageFormatPNG.h"
#include "LucusImage.h"

#include <png.h>

using namespace LucusEngine;

static void _pngRead ( png_structp png, png_bytep buffer, png_size_t size ) {

//    ZLStream* stream = ( ZLStream* )png_get_io_ptr ( png );
//    stream->ReadBytes ( buffer, ( u32 )size );
    std::ifstream* stream = (std::ifstream*)png_get_io_ptr( png );
    stream->read( (char*)buffer, size );
}

ImageFormatPNG::ImageFormatPNG()
{
    //
}

ImageFormatPNG::~ImageFormatPNG()
{
    //
}

bool ImageFormatPNG::OpenFile(const char* path)
{
    mStream = std::ifstream(path, std::ios::in | std::ios::binary);
    
    return mStream.is_open();
}

void ImageFormatPNG::LoadImage(Image* image, cc8* name)
{
    if (!OpenFile(name))
    {
        std::cout << "Error opening image: " << name << std::endl;
        
        return;
    }
    
    png_structp png = png_create_read_struct( PNG_LIBPNG_VER_STRING, 0, 0, 0 );
    if ( !png )
    {
        std::cout << "Error create png struct: " << name << std::endl;
        return;
    }
    
    png_infop pngInfo = png_create_info_struct( png );
    if ( pngInfo )
    {
        png_set_read_fn( png, &mStream, _pngRead );
        
//        ReadImage
        png_read_info( png, pngInfo );
        
        png_uint_32 width;
        png_uint_32 height;
        int bitDepth;
        int pngColorType;
        int interlaceType;
        
        png_get_IHDR( png, pngInfo, &width, &height, &bitDepth, &pngColorType, &interlaceType, 0, 0 );
        
        int paletteSize = 0;
        png_colorp palette;
        
        png_get_PLTE( png, pngInfo, &palette, &paletteSize );
        
        int transSize = 0;
        png_bytep trans;
        
        png_get_tRNS( png, pngInfo, &trans, &transSize, 0 );
        
        std::cout << "PNG: " << width << " " << height << " bitDepth:" << bitDepth << " pngColorType:" << pngColorType  << " interlaceType:" << interlaceType << std::endl;
        std::cout << "---: pallete:" << palette << " size:" << paletteSize << std::endl;
		// why trans fails for win build. trans is nil? mb nil in xcode but it's not fail
        //std::cout << "---: trans:" << trans << " size:" << transSize << std::endl;
        
        bool trueColor = true;
        bool hasAlpha = false;
        
//        png_set_sig_bytes(png, 8);
        // Read the entire image into memory.
//        png_read_png( png, pngInfo, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, 0 );
//        png_set_packing( png );
//        png_set_strip_16( png );
//        png_set_expand( png );
        //
//        png_read_update_info( png, pngInfo );
        
//        width = png_get_image_width( png, pngInfo );
//        height = png_get_image_height( png, pngInfo );
////
//        png_byte colorType = png_get_color_type( png, pngInfo );
////
//        std::cout << "---: read with params:" << width << " " << height << " colorType:" << (u32)colorType << std::endl;
        
        switch(pngColorType) //pngColorType
        {
            case PNG_COLOR_TYPE_RGBA: // 4 bytes = 32 bits
                trueColor = true;
                hasAlpha = true;
                break;
            case PNG_COLOR_TYPE_RGB: // 3 bytes = 24 bits
                trueColor = true;
                hasAlpha = false;
                break;
            case PNG_COLOR_TYPE_PALETTE: // 1 bytes = 8 bits
                
//                png_set_palette_to_rgb( png ); // like simple RGB
//                trueColor = true;
                
                // like Indexed image format
                trueColor = false;
                hasAlpha = (transSize) ? true : false;
                break;
            default:
                break;
        }
        
//        png_read_update_info( png, pngInfo );
        
        
        
        if (trueColor)
        {
//            if (hasAlpha)
            
                size_t stride = png_get_rowbytes( png, pngInfo );
                std::cout << "PNG: row size:" << stride << " height:" << height << std::endl;
                
        //        char* data = new char[stride * height];
                
                // buffer
                png_byte* buffer = new png_byte[stride * height];
                
                // read rows into data
                png_bytepp rows = png_get_rows( png, pngInfo );
                std::cout << "PNG: start read rows! rowspp:" << rows << std::endl;
                
                for (unsigned char i = 0; i < height; ++i)
                {
        //            png_read_row( png, (png_bytep)((size_t)buffer + ( i * stride )), 0);
                    png_read_row( png, buffer + ( i * stride ), 0);
        //            memcpy(buffer + (stride * (height - 1 - i)), rows[i], stride);
                }
                
                u32 pixelDataSize = static_cast<u32>(stride * height);
                std::cout << "PNG: finished! pixelDataSize: " << pixelDataSize << std::endl;
                
                if (hasAlpha)
                {
                    image->Load(width, height, (char*)buffer, pixelDataSize);
                }
                else
                {
                    // RGB format
                    image->Load24(width, height, (char*)buffer, pixelDataSize);
                }
                
                delete [] buffer;
        }
        else
        {
            // Indexed format
            
            size_t rowSize = png_get_rowbytes( png, pngInfo );
            std::cout << "PNG: pallete types:" << rowSize << std::endl;
            
            u32* palletes = new u32[paletteSize];
            
            for ( u32 i = 0; i < paletteSize; ++i )
            {
                unsigned char r = palette[i].red;
                unsigned char g = palette[i].green;
                unsigned char b = palette[i].blue;
                unsigned char a = i < transSize ? trans[i] : 0xff;
                
                u32 color = (r << 0x00) + (g << 0x08) + (b << 0x10) + (a << 0x18);
//                u32 color = (r << 0x18) + (g << 0x10) + (b << 0x08) + (a << 0x00);
                // Set Pallete Color
                palletes[i] = color;
            }
            
            u32 pixelDataSize = static_cast<u32>(rowSize * height);
            
            png_byte* indexes = new png_byte[pixelDataSize];
            
            for ( u32 i = 0; i < height; ++i )
            {
                png_read_row( png, indexes + ( i * rowSize ), 0);
            }
            
//            for (int j = 0; j < height; ++j )
//            {
//                for ( int i = 0; i < width; ++i )
//                {
//                    char idx = indexes[j * height + i];
//                    u32 color = 0;
//                    std::cout << " : [" << i << "," << j << "] = " << (int)idx << " color: " << color << std::endl;
//                }
//            }
            
            image->LoadIndexed(width, height, (char*)indexes, palletes, paletteSize);
            
            delete [] indexes;
            delete [] palletes;
        }

    }
    
    png_destroy_read_struct( &png, &pngInfo, 0 );
}
