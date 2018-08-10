#include <iostream>
#include "AnimationManager.h"

AnimationManager::AnimationManager() : stopTime(std::chrono::steady_clock::now()), running(false)
{
}

void AnimationManager::Start()
{
    if(!running)
    {
        auto elapsedTime = std::chrono::steady_clock::now() - stopTime;
        for(AnimationWithStartTime animPair : animationList)
        {
            animPair.first += elapsedTime;
        }
        running = true;
    }
}

void AnimationManager::Stop()
{
    running = false;
    stopTime = std::chrono::steady_clock::now();
}

void AnimationManager::Tick()
{
    if(running)
    {
        auto timeNow = std::chrono::steady_clock::now();
        DBGPRINT("AnimationManager::Tick()" << std::endl);
        for(AnimationList::iterator animPairIt = animationList.begin(); animPairIt != animationList.end();)
        {
            AnimationWithStartTime& animPair = *animPairIt;
            std::chrono::duration<double, std::milli> elapsedTime = timeNow - animPair.first;
            DBGPRINT("Processing animation with elapsed time - " << elapsedTime.count() << std::endl);
            if(!animPair.second->InvokeSetter(static_cast<unsigned int>(elapsedTime.count())))
            {
                animPairIt = animationList.erase(animPairIt);
            }
            else
            {
                ++animPairIt;
            }
        }
    }
}

void AnimationManager::AddAnimation(std::shared_ptr<IAnimation>& anim)
{
    auto timeNow = std::chrono::steady_clock::now();

    animationList.emplace_back(timeNow, anim);
}
