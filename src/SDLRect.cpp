#include "SDLRect.h"

SDLRect::SDLRect()
{
}

SDLRect::SDLRect(int x, int y, int w, int h)
{
    rawRect.x = x;
    rawRect.y = y;
    rawRect.w = w;
    rawRect.h = h;
}

SDLRect::~SDLRect()
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

SDL_Rect * SDLRect::GetRawHandle()
{
    return &rawRect;
}
