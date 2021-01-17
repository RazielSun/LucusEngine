//
//  TimeManager.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 09/03/2020.
//

#ifndef _LUCUS_ENGINE_TIME_MANAGER_H
#define _LUCUS_ENGINE_TIME_MANAGER_H

#include <chrono>

using HighResClock = std::chrono::high_resolution_clock;
using HighResTimePoint = std::chrono::time_point<HighResClock>;

namespace LucusEngine
{
    class TimeManager
    {
    public:
        TimeManager() noexcept;
        
        void Reset();
        void UpdateTime();
        float GetDeltaSeconds();
        float GetElapsedSeconds();
        void SetUnusedSeconds(float seconds);
        
    protected:
//        u32 mFrameCounter;
        float mElapsedSeconds;
        float mDeltaSeconds;
        float mUnusedSeconds;
        
        HighResClock mClock;
        HighResTimePoint mLastTime;
    };
}

#endif /* _LUCUS_ENGINE_TIME_MANAGER_H */
