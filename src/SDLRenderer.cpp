#include "SDLRenderer.h"



SDLRenderer::SDLRenderer(std::shared_ptr<SDLWindow> window) : renderer_handle(SDL_CreateRenderer(window->GetRawHandle(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), sdl_deleter()), sdlWindow(window)
{
}


SDLRenderer::~SDLRenderer()
{
}

void SDLRenderer::Clear()
{
    SDL_RenderClear(renderer_handle.get());
}

void SDLRenderer::Draw(std::shared_ptr<SDLTexture> texture, SDLRect& srcRect, SDLRect& dstRect, double rotation)
{
    SDL_RenderCopyEx(renderer_handle.get(), texture->GetRawHandle(), srcRect.GetRawHandle(), dstRect.GetRawHandle(), rotation, nullptr, SDL_FLIP_NONE);
}

void SDLRenderer::RenderPresent()
{
    SDL_RenderPresent(renderer_handle.get());
}

SDL_Surface * SDLRenderer::GetRenderSurfaceRaw()
{
    return SDL_GetWindowSurface(sdlWindow->GetRawHandle());
}

SDL_Renderer * SDLRenderer::GetRawHandle()
{
    return renderer_handle.get();
}
