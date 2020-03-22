//
//  LucusTexture.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 22/03/2020.
//

#ifndef _LUCUS_ENGINE_TEXTURE_H
#define _LUCUS_ENGINE_TEXTURE_H

namespace LucusEngine
{
    class Image;
    
    class Texture
    {
    public:
        Texture();
        virtual ~Texture();
        
        virtual void InitFromImage( Image* image ) = 0;
    };
}

#endif /* _LUCUS_ENGINE_TEXTURE_H */
