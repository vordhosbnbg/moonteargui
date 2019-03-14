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

void SDLRenderer::Draw(std::shared_ptr<SDLTexture>& texture, SDLRect& srcRect, SDLRect& dstRect, double rotation)
{
    SDL_RenderCopyEx(renderer_handle.get(), texture->GetRawHandle(), srcRect.GetRawHandle(), dstRect.GetRawHandle(), rotation, nullptr, SDL_FLIP_NONE);
}

void SDLRenderer::DrawLineOnTexture(std::shared_ptr<SDLTexture>& targetTexture, int x1, int y1, int x2, int y2)
{
    SDL_SetRenderTarget(renderer_handle.get(), targetTexture->GetRawHandle());
    SDL_SetRenderDrawColor(renderer_handle.get(), 0xFF, 0xFF, 0xFF, 0);
    SDL_RenderDrawLine(renderer_handle.get(), x1, y1, x2, y2);
    SDL_SetRenderDrawColor(renderer_handle.get(), 0x0, 0x0, 0x0, 0);
    SDL_SetRenderTarget(renderer_handle.get(), nullptr);
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
