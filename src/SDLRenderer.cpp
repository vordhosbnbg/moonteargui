#include "SDLRenderer.h"



SDLRenderer::SDLRenderer(shared_ptr<SDLWindow> window) : renderer_handle(SDL_CreateRenderer(window->GetRawHandle(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), sdl_deleter())
{
}


SDLRenderer::~SDLRenderer()
{
}

SDL_Renderer * SDLRenderer::GetRawHandle()
{
    return renderer_handle.get();
}
