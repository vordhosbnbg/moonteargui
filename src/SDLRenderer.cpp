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

void SDLRenderer::DrawF(SDLTexture& texture, SDLRect& srcRect, SDLFRect& dstRect, double rotation)
{
    SDL_RenderCopyExF(renderer_handle.get(), texture.GetRawHandle(), srcRect.GetRawHandle(), dstRect.GetRawHandle(), rotation, nullptr, SDL_FLIP_NONE);
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

void SDLRenderer::DrawLineOnTextureF(SDLTexture& targetTexture, const SDL_Color& color, float x1, float y1, float x2, float y2)
{
    SDL_Renderer * renderer = renderer_handle.get();
    SDL_Color prevColor;

    SDL_GetRenderDrawColor(renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
    SDL_SetRenderTarget(renderer, targetTexture.GetRawHandle());
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);

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

void SDLRenderer::DrawRectangleOnTextureF(SDLTexture& targetTexture, const SDL_Color& color, float x1, float y1, float x2, float y2)
{
    SDL_Renderer * renderer = renderer_handle.get();
    SDL_Color prevColor;

    SDL_GetRenderDrawColor(renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
    SDL_SetRenderTarget(renderer, targetTexture.GetRawHandle());
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect{x1, y1, x2, y2};
    SDL_RenderDrawRectF(renderer, &rect);

    // restore color and default render target
    SDL_SetRenderDrawColor(renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
    SDL_SetRenderTarget(renderer, nullptr);
}

void SDLRenderer::DrawPointsOnTextureF(SDLTexture& targetTexture, float xOffset, float yOffset, float width, float height, const std::vector<SDL_Color>& points)
{
    SDL_Renderer * renderer = renderer_handle.get();
    SDL_Color prevColor;

    SDL_GetRenderDrawColor(renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
    SDL_SetRenderTarget(renderer, targetTexture.GetRawHandle());
    for(int x = 0; x < width; ++x)
    {
        for(int y = 0; y < height; ++y)
        {
            const SDL_Color point = points[y*x];
            SDL_SetRenderDrawColor(renderer, point.r, point.g, point.b, point.a);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }

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
