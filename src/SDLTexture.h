#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H
#include <memory>
#include "SDL.h"
#include "SdlDeleter.h"
#include "SDLRenderer.h"
#include "SDLSurface.h"

using namespace std;
class SDLTexture
{
public:
    SDLTexture(shared_ptr<SDLRenderer> renderer, shared_ptr<SDLSurface> surface);
    ~SDLTexture();

private:
    unique_ptr<SDL_Texture, sdl_deleter> texture_handle;
};
#endif //SDLTEXTURE_H
