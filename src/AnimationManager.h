#pragma once

#include <memory>
#include <list>
#include <chrono>
#include "Animation.h"

using MillisecondTimePoint = std::chrono::steady_clock::time_point;
using AnimationWithStartTime = std::pair<MillisecondTimePoint,std::shared_ptr<IAnimation>>;
using AnimationList = std::list<AnimationWithStartTime>;

class AnimationManager
{
public:

    AnimationManager();

    void Start();
    void Stop();

    void Tick();
    void AddAnimation(std::shared_ptr<IAnimation>& anim);

private:

    AnimationList animationList;
    MillisecondTimePoint startTime;
    MillisecondTimePoint stopTime;
    bool running;

};
