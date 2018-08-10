#pragma once
#include <functional>
#include <iostream>
#include "utils.h"


class IAnimation
{
public:

    virtual ~IAnimation(){}
    virtual bool InvokeSetter(unsigned int elapsedTimeInMs) = 0;
};

template<typename AnimatedType, typename AnimatedObject>
class Animation : public IAnimation
{
public:
    Animation(AnimatedObject& object,
              std::function<void(AnimatedObject&, AnimatedType)> setterMethod,
              AnimatedType from,
              AnimatedType to,
              unsigned int durationInMs,
              bool loop = false)
        : animatedObject(object),
          setterFunction(setterMethod),
          animatedFrom(from),
          animatedTo(to),
          animationDuration(durationInMs),
          isLooping(loop)
    {

    }
    virtual ~Animation(){}

    virtual bool InvokeSetter(unsigned int elapsedTimeInMs) override
    {
        DBGPRINT("Animation::InvokeSetter() - " << elapsedTimeInMs << std::endl);
        bool retVal = true;
        if(isLooping)
        {
            elapsedTimeInMs = elapsedTimeInMs % animationDuration;
        }
        else if(elapsedTimeInMs > animationDuration)
        {
            elapsedTimeInMs = animationDuration;
            retVal = false;
        }
        if(setterFunction && elapsedTimeInMs <= animationDuration)
        {
            AnimatedType valueToSet = animatedFrom + (animatedTo - animatedFrom) * (static_cast<double>(elapsedTimeInMs) / static_cast<double>(animationDuration));
            DBGPRINT("animatedFrom: " << animatedFrom << ", animatedTo: " << animatedTo << ", elapsedTimeInMs: " << elapsedTimeInMs << ", animationDuration: " << animationDuration << std::endl);
            DBGPRINT("valueToSet: " << valueToSet << std::endl)
            setterFunction(animatedObject, valueToSet);
        }

        return retVal;
    }
private:
    std::function<void(AnimatedObject&, AnimatedType)> setterFunction;
    AnimatedObject& animatedObject;
    AnimatedType animatedFrom;
    AnimatedType animatedTo;

    unsigned int animationDuration;
    bool isLooping = true;
};
