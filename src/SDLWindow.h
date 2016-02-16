#ifndef SDLWINDOW_H
#define SDLWINDOW_H
#include <memory>
#include "SDL.h"
#include "SdlDeleter.h"

using namespace std;
class SDLWindow 
{
public:
    SDLWindow();
    ~SDLWindow();

private:
    unique_ptr<SDL_Window, sdl_deleter> window_handle;
};
#endif //SDLWINDOW_H
