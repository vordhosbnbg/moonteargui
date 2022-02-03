#pragma once
#include "SDL.h"

class SDLFRect
{
public:
    SDLFRect() : rawRect{} {}

    SDLFRect(const SDLFRect& other) = default;
    SDLFRect(SDLFRect&& other) = default;
    SDLFRect(float x, float y, float w, float h) : rawRect{x, y, w, h} {}
    SDLFRect& operator=(const SDLFRect& other) = default;
    SDLFRect& operator=(SDLFRect&& other) = default;
    ~SDLFRect() = default;

    void SetX(float x)
    {
        rawRect.x = x;
    }
    void SetY(float y)
    {
        rawRect.y = y;
    }
    void SetW(float w)
    {
        rawRect.w = w;
    }
    void SetH(float h)
    {
        rawRect.h = h;
    }
    float GetX()
    {
        return rawRect.x;
    }
    float GetY()
    {
        return rawRect.y;
    }
    float GetW()
    {
        return rawRect.w;
    }
    float GetH()
    {
        return rawRect.h;
    }

    SDL_FRect * GetRawHandle()
    {
        return &rawRect;
    }


private:
    SDL_FRect rawRect;
};
