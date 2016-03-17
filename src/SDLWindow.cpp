#include "SDLWindow.h"

SDLWindow::SDLWindow(const char * title, int posX, int posY, int width, int height) : window_handle(SDL_CreateWindow(title, posX, posY, width, height, SDL_WINDOW_SHOWN), sdl_deleter())
{
    windowID = SDL_GetWindowID(window_handle.get());
}

SDLWindow::~SDLWindow()
{
}

SDL_Window * SDLWindow::GetRawHandle()
{
    return window_handle.get();
}

void SDLWindow::Hide()
{
    SDL_HideWindow(window_handle.get());
}

void SDLWindow::Show()
{
    SDL_ShowWindow(window_handle.get());
}
