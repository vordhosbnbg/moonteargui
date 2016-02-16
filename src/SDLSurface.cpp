#include "SDLSurface.h"
#include "SDL_image.h"

SDLSurface::SDLSurface(string filename) : surface_handle(IMG_Load(filename.c_str()), sdl_deleter())
{
}

SDLSurface::~SDLSurface()
{
}

SDL_Surface * SDLSurface::GetRawHandle()
{
    return surface_handle.get();
}
