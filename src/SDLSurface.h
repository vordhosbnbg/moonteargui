#ifndef SDLSURFACE_H
#define SDLSURFACE_H
#include <memory>
#include <string>
#include "SDL.h"
#include "SdlDeleter.h"

class SDLSurface
{
public:
    SDLSurface(std::string filename);
    ~SDLSurface();

    SDL_Surface * GetRawHandle();
private:
    std::unique_ptr<SDL_Surface, sdl_deleter> surface_handle;
};
#endif //SDLSURFACE_H
