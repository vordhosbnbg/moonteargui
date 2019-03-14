#include "SDLRect.h"

SDLRect::SDLRect() : rawRect{0,0,0,0}
{
}

SDLRect::SDLRect(int x, int y, int w, int h) : rawRect{x,y,w,h}
{
}


void SDLRect::SetX(int x)
{
    rawRect.x = x;
}

void SDLRect::SetY(int y)
{
    rawRect.y = y;
}

void SDLRect::SetW(int w)
{
    rawRect.w = w;
}

void SDLRect::SetH(int h)
{
    rawRect.h = h;
}

int SDLRect::GetX()
{
    return rawRect.x;
}

int SDLRect::GetY()
{
    return rawRect.y;
}

int SDLRect::GetW()
{
    return rawRect.w;
}

int SDLRect::GetH()
{
    return rawRect.h;
}

SDL_Rect * SDLRect::GetRawHandle()
{
    return &rawRect;
}
