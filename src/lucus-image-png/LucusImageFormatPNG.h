//
//  LucusImageFormatPNG.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 21/03/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#ifndef _LUCUS_ENGINE_IMAGE_FORMAT_PNG_H
#define _LUCUS_ENGINE_IMAGE_FORMAT_PNG_H

#include "LucusImageFormat.h"

namespace LucusEngine
{
	class Image;

	class ImageFormatPNG : public ImageFormat
	{
	private:
	    std::ifstream mStream;
	    
	public:
	    ImageFormatPNG();
	    virtual ~ImageFormatPNG();
	    
	    bool OpenFile(cc8* path);
	    virtual void LoadImage(Image* image, cc8* name) override;
	};
}



#endif /* _LUCUS_ENGINE_IMAGE_FORMAT_PNG_H */
