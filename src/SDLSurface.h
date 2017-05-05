#ifndef SDLSURFACE_H
#define SDLSURFACE_H
#include <memory>
#include <string>
#include "SDL2/SDL.h"
#include "SDLDeleter.h"

class SDLSurface
{
public:
    SDLSurface(std::string filename);
    SDLSurface(SDL_Surface * surface);
    ~SDLSurface();

    void Fill(SDL_Color color);
    void SetBlendMode(SDL_BlendMode mode);
    SDL_Surface * GetRawHandle();
private:
    std::unique_ptr<SDL_Surface, sdl_deleter> surface_handle;
};
#endif //SDLSURFACE_H
