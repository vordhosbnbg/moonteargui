#include "SDLSurface.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_image.h"


SDLSurface::SDLSurface(std::string filename) : surface_handle(IMG_Load(filename.c_str()), sdl_deleter())
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

void SDLSurface::SetBlendMode(SDL_BlendMode mode)
{
    SDL_SetSurfaceBlendMode(surface_handle.get(), mode);
}

SDL_Surface * SDLSurface::GetRawHandle()
{
    return surface_handle.get();
}
