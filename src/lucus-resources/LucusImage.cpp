//
//  LucusImage.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 21/03/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#include "LucusCore.h"
#include "LucusFileSystem.h"
#include "LucusImageFormatManager.h"
#include "LucusImage.h"
#include "LucusImageFormat.h"

#include <string> // for memcpy char

using namespace LucusEngine;

Image::Image() : mWidth(0), mHeight(0), mBitmap(0)
{
}

Image::~Image()
{
}

Image::Image(u32 width, u32 height, char* pixelData, u32 pixelDataSize) : mWidth(width), mHeight(height)
{
    ReadData(pixelData, pixelDataSize);
}

void Image::Load( cc8* name )
{
    std::string formatName = Core::GetFileSystem()->GetFileFormat( name );
    ImageFormat* imageFormat = Core::GetImageFormatMgr()->FindFormat( formatName.c_str() );
    if (nullptr != imageFormat)
    {
        imageFormat->LoadImage(this, Core::GetFileSystem()->GetAssetPath(name).c_str());
    }
}

void Image::Load(u32 width, u32 height, char* pixelData, u32 pixelDataSize)
{
    mWidth = width;
    mHeight = height;
    ReadData(pixelData, pixelDataSize);
}

void Image::Load24(u32 width, u32 height, char* pixelData, u32 pixelDataSize)
{
    mWidth = width;
    mHeight = height;
    u32 newPixelDataSize = width * height * 4;
    mBitmap = new char[newPixelDataSize];
    
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            int indexSrc = (j * height + i) * 3;
            int indexDst = (j * height + i) * 4;
            
            ((char*)mBitmap)[indexDst+0] = pixelData[indexSrc+0];
            ((char*)mBitmap)[indexDst+1] = pixelData[indexSrc+1];
            ((char*)mBitmap)[indexDst+2] = pixelData[indexSrc+2];
            ((char*)mBitmap)[indexDst+3] = 0xff;
        }
    }
}

void Image::LoadIndexed(u32 width, u32 height, char* indexes, u32* pallete, u32 palleteSize)
{
    mWidth = width;
    mHeight = height;
    
    u32 pixelDataSize = width * height * 4;
    mBitmap = new char[pixelDataSize];
    
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            u32 idx = j * height + i;
            u32 pIdx = (u32)indexes[idx];
            u32 color = 0;
            if (pIdx >= 0 && pIdx < palleteSize)
                color = pallete[pIdx];
            
            ((u32*)mBitmap)[idx] = color;
        }
    }
}

void Image::ReadData(char* pixelData, u32 pixelDataSize)
{
    mBitmap = new char[pixelDataSize];
    memcpy(mBitmap, pixelData, pixelDataSize);
}
