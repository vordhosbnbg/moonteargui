#ifndef SDLRENDERER_H
#define SDLRENDERER_H
#include <memory>
#include "SDL.h"
#include "SdlDeleter.h"
#include "SDLWindow.h"
#include "SDLTexture.h"
#include "SDLRect.h"

class SDLTexture;
class SDLRenderer
{
public:
    SDLRenderer(std::shared_ptr<SDLWindow> window);
    ~SDLRenderer();

    void Clear();
    void Draw(std::shared_ptr<SDLTexture> texture, SDLRect& srcRect, SDLRect& dstRect, double rotation = 0);
    void RenderPresent();
    SDL_Renderer * GetRawHandle();

private:
    std::unique_ptr<SDL_Renderer, sdl_deleter> renderer_handle;

};

#endif //SDLRENDERER_H
