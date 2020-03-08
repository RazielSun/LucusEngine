//
//  LucusViewport.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 6/03/2020.
//

#ifndef _LUCUS_ENGINE_VIEWPORT_H
#define _LUCUS_ENGINE_VIEWPORT_H

#include "LucusTypes.h"

namespace LucusEngine
{

    class Viewport
    {
    protected:
    	float mLeft, mTop, mWidth, mHeight;

    public:
        Viewport(float left, float top, float width, float height);
        Viewport();
        
        ~Viewport();

        void ChangeSize(float width, float height);
        void ChangeOirigin(float left, float top);

        float GetLeft() const { return mLeft; }
        float GetTop() const { return mTop; }
        float GetRight() const { return mLeft + mWidth; }
        float GetBottom() const { return mTop + mHeight; }
        float GetWidth() const { return mWidth; }
        float GetHeight() const { return mHeight; }
        float GetAspectRatio() const { return mWidth / mHeight; }
    };
}

#endif /* _LUCUS_ENGINE_VIEWPORT_H */
