#include "SDLSurface.h"
#include "SDL_image.h"
using namespace std;

SDLSurface::SDLSurface(string filename) : surface_handle(IMG_Load(filename.c_str()), sdl_deleter())
{
}

SDLSurface::SDLSurface(SDL_Surface *surface) : surface_handle(surface)
{
}

SDLSurface::~SDLSurface()
{
}

void SDLSurface::Fill(SDL_Color color)
{
    SDL_FillRect(surface_handle.get(), NULL, SDL_MapRGBA(surface_handle.get()->format, color.r, color.g, color.b, color.a));
}

SDL_Surface * SDLSurface::GetRawHandle()
{
    return surface_handle.get();
}
