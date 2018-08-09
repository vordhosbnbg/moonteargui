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
        std::cout << "AnimationManager::Tick()" << std::endl;
        for(AnimationWithStartTime animPair : animationList)
        {
            std::chrono::duration<double, std::milli> elapsedTime = timeNow - animPair.first;
            std::cout << "Processing animation with elapsed time - " << elapsedTime.count() << std::endl;
            animPair.second->InvokeSetter(static_cast<unsigned int>(elapsedTime.count()));
        }
    }
}

void AnimationManager::AddAnimation(std::shared_ptr<IAnimation>& anim)
{
    auto timeNow = std::chrono::steady_clock::now();

    animationList.emplace_back(timeNow, anim);
}
