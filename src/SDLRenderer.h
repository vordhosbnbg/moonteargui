#ifndef SDLRENDERER_H
#define SDLRENDERER_H
#include <memory>
#include "SDL.h"
#include "SdlDeleter.h"

using namespace std;
class SDLRenderer
{
public:
    SDLRenderer();
    ~SDLRenderer();

private:
    unique_ptr<SDL_Renderer, sdl_deleter> renderer_handle;

};

#endif //SDLRENDERER_H
