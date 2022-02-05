#pragma once

#include <memory>
#include <string>
#include "SDL.h"
#include "SDLDeleter.h"

class SDLSurface
{
public:
    SDLSurface(int w, int h);
    SDLSurface(SDLSurface&& other);
    SDLSurface(std::string& filename);
    SDLSurface(SDL_Surface* surface);
    ~SDLSurface();

    void Fill(const SDL_Color& color);
    void SetBlendMode(SDL_BlendMode mode);
    SDL_Surface * GetRawHandle();
    void SaveToPNG(const char* filename);

private:
    std::unique_ptr<SDL_Surface, sdl_deleter> surface_handle;
};
