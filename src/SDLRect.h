#pragma once

#include "SDL.h"

class SDLRect 
{
public:
    SDLRect();
    SDLRect(const SDLRect& other) = default;
    SDLRect(SDLRect&& other) = default;
    SDLRect(int x, int y, int w, int h);
    SDLRect& operator=(const SDLRect& other) = default;
    SDLRect& operator=(SDLRect&& other) = default;
    ~SDLRect() = default;

    void SetX(int x);
    void SetY(int y);
    void SetW(int w);
    void SetH(int h);
    int GetX();
    int GetY();
    int GetW();
    int GetH();

    SDL_Rect * GetRawHandle();

private:
    SDL_Rect rawRect;
};
