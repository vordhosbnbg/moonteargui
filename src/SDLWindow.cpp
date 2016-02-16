#include "SDLWindow.h"

SDLWindow::SDLWindow(const char * title, int posX, int posY, int width, int height) : window_handle(SDL_CreateWindow(title, posX, posY, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL), sdl_deleter())
{
}

SDLWindow::~SDLWindow()
{
}

SDL_Window * SDLWindow::GetRawHandle()
{
    return window_handle.get();
}
