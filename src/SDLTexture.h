#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H
#include <memory>
#include "SDL2/SDL.h"
#include "SDLDeleter.h"
#include "SDLRenderer.h"
#include "SDLSurface.h"

class SDLRenderer;
class SDLTexture
{
public:
    SDLTexture(std::shared_ptr<SDLRenderer> renderer, std::shared_ptr<SDLSurface> surface);
    ~SDLTexture();

    SDL_Texture * GetRawHandle();
    int GetWidth();
    int GetHeight();

private:
    std::unique_ptr<SDL_Texture, sdl_deleter> texture_handle;
    std::shared_ptr<SDLRenderer> sdlRenderer; // keep renderer alive, while texture is alive
};
#endif //SDLTEXTURE_H
