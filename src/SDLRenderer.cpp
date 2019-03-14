#include "SDLRenderer.h"



SDLRenderer::SDLRenderer(std::shared_ptr<SDLWindow> window) : renderer_handle(SDL_CreateRenderer(window->GetRawHandle(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), sdl_deleter()), sdlWindow(window)
{
}


void SDLRenderer::Clear()
{
    SDL_RenderClear(renderer_handle.get());
}

void SDLRenderer::Clear(const SDL_Color& color)
{
    SDL_Renderer * renderer = renderer_handle.get();
    SDL_Color prevColor;

    SDL_GetRenderDrawColor(renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);

    // restore color and default render target
    SDL_SetRenderDrawColor(renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
}

void SDLRenderer::Draw(SDLTexture& texture, SDLRect& srcRect, SDLRect& dstRect, double rotation)
{
    SDL_RenderCopyEx(renderer_handle.get(), texture.GetRawHandle(), srcRect.GetRawHandle(), dstRect.GetRawHandle(), rotation, nullptr, SDL_FLIP_NONE);
}

void SDLRenderer::DrawLineOnTexture(SDLTexture& targetTexture, const SDL_Color& color, int x1, int y1, int x2, int y2)
{
    SDL_Renderer * renderer = renderer_handle.get();
    SDL_Color prevColor;

    SDL_GetRenderDrawColor(renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
    SDL_SetRenderTarget(renderer, targetTexture.GetRawHandle());
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    // restore color and default render target
    SDL_SetRenderDrawColor(renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
    SDL_SetRenderTarget(renderer, nullptr);
}

void SDLRenderer::DrawRectangleOnTexture(SDLTexture& targetTexture, const SDL_Color& color, int x1, int y1, int x2, int y2)
{
    SDL_Renderer * renderer = renderer_handle.get();
    SDL_Color prevColor;

    SDL_GetRenderDrawColor(renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
    SDL_SetRenderTarget(renderer, targetTexture.GetRawHandle());
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect{x1, y1, x2, y2};
    SDL_RenderDrawRect(renderer, &rect);

    // restore color and default render target
    SDL_SetRenderDrawColor(renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
    SDL_SetRenderTarget(renderer, nullptr);
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

void SDLRenderer::ClearTexture(const SDL_Color& color, SDLTexture& texture)
{
    SDL_Renderer * renderer = renderer_handle.get();
    SDL_Color prevColor;

    SDL_GetRenderDrawColor(renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
    SDL_SetRenderTarget(renderer, texture.GetRawHandle());
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);

    // restore color and default render target
    SDL_SetRenderDrawColor(renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
    SDL_SetRenderTarget(renderer, nullptr);
}
