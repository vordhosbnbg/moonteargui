#ifndef SDLSURFACE_H
#define SDLSURFACE_H
#include <memory>
#include "SDL.h"
#include "SdlDeleter.h"

using namespace std;
class SDLSurface
{
public:
    SDLSurface();
    ~SDLSurface();

private:
    unique_ptr<SDL_Texture, sdl_deleter> texture_handle;
};
#endif //SDLSURFACE_H
