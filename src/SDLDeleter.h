#ifndef SDLDELETER_H
#define SDLDELETER_H
#include "SDL.h"
struct sdl_deleter
{
    void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
    void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
    void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
    void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); }
};

#endif // SDLDELETER_H
