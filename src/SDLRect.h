#pragma once

#include "SDL.h"

class SDLRect 
{
public:
    SDLRect() : rawRect{} {}
    SDLRect(const SDLRect& other) = default;
    SDLRect(SDLRect&& other) = default;
    SDLRect(int x, int y, int w, int h) : rawRect{x, y, w, h} {}
    SDLRect& operator=(const SDLRect& other) = default;
    SDLRect& operator=(SDLRect&& other) = default;
    ~SDLRect() = default;

    void SetX(int x)
    {
        rawRect.x = x;
    }
    void SetY(int y)
    {
        rawRect.y = y;
    }
    void SetW(int w)
    {
        rawRect.w = w;
    }
    void SetH(int h)
    {
        rawRect.h = h;
    }
    int GetX()
    {
        return rawRect.x;
    }
    int GetY()
    {
        return rawRect.y;
    }
    int GetW()
    {
        return rawRect.w;
    }
    int GetH()
    {
        return rawRect.h;
    }

    SDL_Rect * GetRawHandle()
    {
        return &rawRect;
    }

private:
    SDL_Rect rawRect;
};
