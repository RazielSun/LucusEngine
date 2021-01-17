//
//  TimeManager.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 09/03/2020.
//

#include "LucusTimeManager.h"

using namespace LucusEngine;

TimeManager::TimeManager() noexcept :
    mElapsedSeconds(0.0f),
    mDeltaSeconds(0.0f),
    mUnusedSeconds(0.0f)
{
    Reset();
}

void TimeManager::Reset()
{
    mLastTime = mClock.now();
}

void TimeManager::UpdateTime()
{
//    mFrameCounter++;
    auto current = mClock.now();
    auto delta = current - mLastTime;
    mLastTime = current;
    
    mDeltaSeconds = static_cast<float>(delta.count() * 1e-9);
    mElapsedSeconds += mDeltaSeconds;
    mDeltaSeconds += mUnusedSeconds;

//        if (mElapsedSeconds > 1.0)
//        {
            // char buffer[500];
            // auto fps = frameCounter / elapsedSeconds;
            // sprintf_s(buffer, 500, "FPS: %f\n", fps);
            // OutputDebugString(buffer);
//            mFrameCounter = 0;
//            mElapsedSeconds = 0.0;
//        }

        //     frameCounter++;
    //     auto t1 = clock.now();
    //     auto deltaTime = t1 - t0;
    //     t0 = t1;

    //     elapsedSeconds += deltaTime.count() * 1e-9;
    //     if (elapsedSeconds > 1.0)
    //     {

    //         frameCounter = 0;
    //         elapsedSeconds = 0.0;
    //     }

    //     // Don't try render in first frame
    //     // if (m_frameCount == 0)
    //     // {
    //     //     return;
    //     // }

    //     if (frameCounter != 0)
    //         Render();
    // }
}

float TimeManager::GetDeltaSeconds()
{
    return mDeltaSeconds;
}

float TimeManager::GetElapsedSeconds()
{
    return mElapsedSeconds;
}

void TimeManager::SetUnusedSeconds(float seconds)
{
    mUnusedSeconds = seconds;
}


