//
//  LucusImageFormatTGA.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 04/01/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#include <iostream>

#include "LucusImageFormatTGA.h"
#include "LucusImage.h"

using namespace LucusEngine;

ImageFormatTGA::ImageFormatTGA()
{
    //
}

ImageFormatTGA::~ImageFormatTGA()
{
    //
}

bool ImageFormatTGA::OpenFile(cc8* path)
{
    mStream = std::ifstream(path, std::ios::in);
    
    return mStream.is_open();
}

void ImageFormatTGA::LoadImage(Image* image, cc8* name)
{
    if (!OpenFile(name))
    {
        std::cout << "Error opening image: " << name << std::endl;
        return;
    }
    
    mStream.seekg(0, std::ios::end);
    
//    int fileSize = (int)stream.tellg();
    
    mStream.seekg(-18, std::ios::end);
    char versionCheck[17] = "";
    mStream.read(versionCheck, 16);
    
    int version = 1;
    if (strcmp(versionCheck, "TRUEVISION-XFILE") == 0)
        version = 2;
//    std::cout << "TGA: " << versionCheck << " " << " version: " << version << std::endl;
    
    mStream.seekg(0, std::ios::beg);
    
    TGAHeader tgaHeader;
    
//    stream.read((char*)&tgaHeader.IDSize, sizeof(tgaHeader.IDSize));
//    stream.read((char*)&tgaHeader.colorMapType, sizeof(tgaHeader.colorMapType));
//    stream.read((char*)&tgaHeader.imageType, sizeof(tgaHeader.imageType));
//
//    stream.read((char*)&tgaHeader.colorMapStart, sizeof(tgaHeader.colorMapStart));
//    stream.read((char*)&tgaHeader.colorMapLength, sizeof(tgaHeader.colorMapLength));
//    stream.read((char*)&tgaHeader.colorMapBpp, sizeof(tgaHeader.colorMapBpp));
//
//    stream.read((char*)&tgaHeader.xOrigin, sizeof(tgaHeader.xOrigin));
//    stream.read((char*)&tgaHeader.yOrigin, sizeof(tgaHeader.yOrigin));
//    stream.read((char*)&tgaHeader.width, sizeof(tgaHeader.width));
//    stream.read((char*)&tgaHeader.height, sizeof(tgaHeader.height));
//    stream.read((char*)&tgaHeader.bitsPerPixel, sizeof(tgaHeader.bitsPerPixel));
//    stream.read((char*)&tgaHeader.descriptor, sizeof(tgaHeader.descriptor));
    
    mStream.read(&tgaHeader.IDSize, sizeof(tgaHeader.IDSize));
    mStream.read(&tgaHeader.colorMapType, sizeof(tgaHeader.colorMapType));
    mStream.read(&tgaHeader.imageType, sizeof(tgaHeader.imageType));
    
    mStream.read((char*)&tgaHeader.colorMapStart, sizeof(tgaHeader.colorMapStart));
    mStream.read((char*)&tgaHeader.colorMapLength, sizeof(tgaHeader.colorMapLength));
    mStream.read(&tgaHeader.colorMapBpp, sizeof(tgaHeader.colorMapBpp));
    
    mStream.read((char*)&tgaHeader.xOrigin, sizeof(tgaHeader.xOrigin));
    mStream.read((char*)&tgaHeader.yOrigin, sizeof(tgaHeader.yOrigin));
    mStream.read((char*)&tgaHeader.width, sizeof(tgaHeader.width));
    mStream.read((char*)&tgaHeader.height, sizeof(tgaHeader.height));
    mStream.read(&tgaHeader.bitsPerPixel, sizeof(tgaHeader.bitsPerPixel));
    mStream.read(&tgaHeader.descriptor, sizeof(tgaHeader.descriptor));
    
    std::cout << "TGA: width: " << tgaHeader.width << " height: " << tgaHeader.height << " bitsPerPixel: " << (int)tgaHeader.bitsPerPixel << "." << std::endl;
    std::cout << "TGA: imageType " << (int)tgaHeader.imageType << std::endl;
    
    std::cout << "TGA: colorMapType " << (int)tgaHeader.colorMapType << std::endl;
    std::cout << "TGA: colorMap ::" << (int)tgaHeader.colorMapStart << " " << (int)tgaHeader.colorMapLength << " " << (int)tgaHeader.colorMapBpp << std::endl;
    
    bool isIndexed = (int)tgaHeader.imageType == 1;
    
    u32 width = tgaHeader.width;
    u32 height = tgaHeader.height;
    u32 bytesPerPixel = 1;
    
    if (tgaHeader.bitsPerPixel == 32)
    {
        bytesPerPixel = 4;
        
        // bits Per Alpha check == 8
    }
    else if (tgaHeader.bitsPerPixel == 24)
    {
        bytesPerPixel = 3;
        
        // bits Per Alpha check == 0
    }
    
    // Image Identification Field.
    unsigned char imageIdentificationField = 0x00;
    mStream.read((char*)&imageIdentificationField, tgaHeader.IDSize);
    
    u32 dstDataSize = width * height * 4;
    dstPixelData = new char[dstDataSize];
    
    if (isIndexed)
    {
        u8 colorMapOrigin = tgaHeader.colorMapStart;
        u32 bytesInColorMap = (u32)tgaHeader.colorMapBpp / 8; // 24 / 8 = 3 bytes
        int colorMapSize = (int)tgaHeader.colorMapLength * bytesInColorMap;
        u8 * colorMap = new u8 [colorMapSize];
        
        std::cout << bytesInColorMap << " " << colorMapSize << std::endl;
        
        // skip some data if color map start in non zero
        // todo
        // (int)tgaHeader.colorMapStart
        
        mStream.read((char*)colorMap, colorMapSize);
        
        u32 srcDataSize = width * height * bytesPerPixel; // 8 bits for store id to color map
        srcPixelData = new char[srcDataSize];
        mStream.read(srcPixelData, srcDataSize);
        
        // indexed
        for (u32 y = 0; y < height; ++y)
        {
            u8 srcRow = y;
            
            for (u32 x = 0; x < width; ++x)
            {
                u8 srcColumn = x;
                u32 mapPixelIndex = srcPixelData[srcRow * width + srcColumn] & 0xff - colorMapOrigin;
                
                u32 dstPixelIndex = (y * width + x) * 4;
                
                // get color from colorMap and BGR to RGB
                int index = mapPixelIndex * bytesInColorMap;

                dstPixelData[dstPixelIndex + 0] = colorMap[index + 2]; // Dst Red
                dstPixelData[dstPixelIndex + 1] = colorMap[index + 1]; // Dst Green
                dstPixelData[dstPixelIndex + 2] = colorMap[index + 0]; // Dst Blue
                
                // Alpha
                if (bytesInColorMap == 3)
                {
                    dstPixelData[dstPixelIndex + 3] = 0xff;
                }
                else
                {
                    // change alpha to real from color map
                    dstPixelData[dstPixelIndex + 3] = colorMap[index + 3];;
                }
            }
        }
        
        delete [] colorMap;
        delete [] srcPixelData;
    }
    else
    {
        // truecolor
        u32 srcDataSize = width * height * bytesPerPixel;//(tgaHeader.bitsPerPixel / 8);
        srcPixelData = new char[srcDataSize];
        mStream.read(srcPixelData, srcDataSize);
        
        // copy data
        // every row
        for (u32 y = 0; y < height; y++)
        {
            u32 srcRow = y;
            
            // every column
            for (u32 x = 0; x < width; x++)
            {
                u32 srcColumn = x;
                
                u32 srcPixelIndex = bytesPerPixel * (srcRow * width + srcColumn);
                u32 dstPixelIndex = 4 * (y * width + x);
                
                dstPixelData[dstPixelIndex + 0] = srcPixelData[srcPixelIndex + 0];
                dstPixelData[dstPixelIndex + 1] = srcPixelData[srcPixelIndex + 1];
                dstPixelData[dstPixelIndex + 2] = srcPixelData[srcPixelIndex + 2];
                
                if (bytesPerPixel == 3)
                {
                    dstPixelData[dstPixelIndex + 3] = 0xff;
                }
                else
                {
                    dstPixelData[dstPixelIndex + 3] = srcPixelData[srcPixelIndex + 3];
                }
            }
        }
        
        delete [] srcPixelData;
    }
    
    image->Load(width, height, dstPixelData, dstDataSize);
    
    delete [] dstPixelData;
}

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
//    uint8_t descriptor;
