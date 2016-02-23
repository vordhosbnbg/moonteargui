#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H
#include <memory>
#include "SDL.h"
#include "SdlDeleter.h"
#include "SDLRenderer.h"
#include "SDLSurface.h"

class SDLRenderer;
class SDLTexture
{
public:
    SDLTexture(SDLRenderer * renderer, std::shared_ptr<SDLSurface> surface);
    ~SDLTexture();

    SDL_Texture * GetRawHandle();
    int GetWidth();
    int GetHeight();

private:
    std::unique_ptr<SDL_Texture, sdl_deleter> texture_handle;
};
#endif //SDLTEXTURE_H
