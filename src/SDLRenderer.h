#ifndef SDLRENDERER_H
#define SDLRENDERER_H
#include <memory>
#include "SDL.h"
#include "SdlDeleter.h"
#include "SDLWindow.h"

using namespace std;
class SDLRenderer
{
public:
    SDLRenderer(shared_ptr<SDLWindow> window);
    ~SDLRenderer();

    SDL_Renderer * GetRawHandle();

private:
    unique_ptr<SDL_Renderer, sdl_deleter> renderer_handle;

};

#endif //SDLRENDERER_H
