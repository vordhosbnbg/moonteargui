#ifndef SDLWINDOW_H
#define SDLWINDOW_H
#include <memory>
#include "SDL.h"
#include "SdlDeleter.h"

using namespace std;
class SDLWindow 
{
public:
    SDLWindow(const char * title, int posX, int posY, int width, int height);
    ~SDLWindow();

    SDL_Window * GetRawHandle();
private:
    unique_ptr<SDL_Window, sdl_deleter> window_handle;
};
#endif //SDLWINDOW_H
