#ifndef SDLSURFACE_H
#define SDLSURFACE_H
#include <memory>
#include <string>
#include "SDL.h"
#include "SdlDeleter.h"

using namespace std;
class SDLSurface
{
public:
    SDLSurface(string filename);
    ~SDLSurface();

    SDL_Surface * GetRawHandle();
private:
    unique_ptr<SDL_Surface, sdl_deleter> surface_handle;
};
#endif //SDLSURFACE_H
