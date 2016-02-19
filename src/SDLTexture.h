#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H
#include <memory>
#include "SDL.h"
#include "SdlDeleter.h"
#include "SDLRenderer.h"
#include "SDLSurface.h"

using namespace std;
class SDLRenderer;
class SDLTexture
{
public:
    SDLTexture(SDLRenderer * renderer, shared_ptr<SDLSurface> surface);
    ~SDLTexture();

    SDL_Texture * GetRawHandle();
    int GetWidth();
    int GetHeight();

private:
    unique_ptr<SDL_Texture, sdl_deleter> texture_handle;
};
#endif //SDLTEXTURE_H
