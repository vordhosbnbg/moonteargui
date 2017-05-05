#pragma once

#include "SDL2/SDL.h"

class SDLRect 
{
public:
    SDLRect();
    SDLRect(int x, int y, int w, int h);
    ~SDLRect();

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
