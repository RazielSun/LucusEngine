//
//  LucusWindow.h
//  LucusGame
//
//  Created by Alexander Kardakov on 12/02/2020.
//

#ifndef _LUCUS_ENGINE_WINDOW_H
#define _LUCUS_ENGINE_WINDOW_H

#include <vector>
#include "LucusTypes.h"

namespace LucusEngine
{
    class RenderWindow
    {
    public:
        RenderWindow(u32 width, u32 height);
        virtual ~RenderWindow();
        
        virtual void ChangeViewportSize(u32 width, u32 height) = 0;

        u32 GetWidth() { return mWidth; }
        u32 GetHeight() { return mHeight; }
        
    protected:
        u32 mWidth;
        u32 mHeight;
    };

    typedef std::vector<RenderWindow*> RenderWindowVector;
}

#endif /* _LUCUS_ENGINE_WINDOW_H */
