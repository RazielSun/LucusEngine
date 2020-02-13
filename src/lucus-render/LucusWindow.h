//
//  LucusWindow.hpp
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
    class Window
    {
    public:
        Window(u32 width, u32 height);
        virtual ~Window();
        
        virtual void ChangeViewportSize(u32 width, u32 height) = 0;
        
    protected:
        u32 mWidth;
        u32 mHeight;
    };

    typedef std::vector<Window*> WindowVector;
}

#endif /* _LUCUS_ENGINE_WINDOW_H */
