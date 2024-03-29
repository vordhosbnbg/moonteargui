#include <iostream>
#include "SDLSurface.h"
#include "SDL_surface.h"
#include "SDL_image.h"


SDLSurface::SDLSurface(int w, int h) :
    surface_handle(
        SDL_CreateRGBSurface(0, w, h, 24, 0x00FF0000, 0x0000FF00, 0x000000FF, 0x00000000)
        )
{
}

SDLSurface::SDLSurface(SDLSurface&& other) : surface_handle(other.surface_handle.release())
{

}

SDLSurface::SDLSurface(std::string& filename) : surface_handle(IMG_Load(filename.c_str()), sdl_deleter())
{
}

SDLSurface::SDLSurface(SDL_Surface* surface) : surface_handle(surface)
{
}

SDLSurface::~SDLSurface()
{
}

void SDLSurface::Fill(const SDL_Color& color)
{
    SDL_FillRect(surface_handle.get(), nullptr, SDL_MapRGBA(surface_handle.get()->format, color.r, color.g, color.b, color.a));
}

void SDLSurface::SetBlendMode(SDL_BlendMode mode)
{
    SDL_SetSurfaceBlendMode(surface_handle.get(), mode);
}

SDL_Surface * SDLSurface::GetRawHandle()
{
    return surface_handle.get();
}

void SDLSurface::SaveToPNG(const char* filename)
{
    if(IMG_SavePNG(surface_handle.get(), filename))
    {
        std::cout << SDL_GetError() << std::endl;
    }
}
