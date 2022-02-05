#pragma once

#include <memory>
#include <vector>
#include "SDL.h"
#include "SDLDeleter.h"
#include "SDLWindow.h"
#include "SDLSurface.h"
#include "SDLTexture.h"
#include "SDLRect.h"
#include "SDLFRect.h"
#include "ColorPoint.h"

class SDLTexture;
class SDLRenderer
{
public:
    SDLRenderer(std::shared_ptr<SDLWindow> window);
    ~SDLRenderer() = default;

    void Clear();
    void Clear(const SDL_Color& color);
    void Draw(SDLTexture& texture, SDLRect& srcRect, SDLRect& dstRect, double rotation = 0);
    void DrawF(SDLTexture& texture, SDLRect& srcRect, SDLFRect& dstRect, double rotation = 0);
    void DrawLineOnTexture(SDLTexture& targetTexture,
                           const SDL_Color& color,
                           int x1,
                           int y1,
                           int x2,
                           int y2);

    void DrawLineOnTextureF(SDLTexture& targetTexture,
                            const SDL_Color& color,
                            float x1,
                            float y1,
                            float x2,
                            float y2);

    void DrawRectangleOnTexture(SDLTexture& targetTexture,
                                const SDL_Color& color,
                                int x1,
                                int y1,
                                int x2,
                                int y2);

    void DrawRectangleOnTextureF(SDLTexture& targetTexture,
                                 const SDL_Color& color,
                                 float x1,
                                 float y1,
                                 float x2,
                                 float y2);

    void DrawPointsOnTexture(SDLTexture& targetTexture,
                              int width,
                              int height,
                              const std::vector<SDL_Color>& points);

    SDLSurface getSurfaceFromTexture(SDLTexture& sourceTexture);
    void RenderPresent();
    SDL_Surface * GetRenderSurfaceRaw();
    SDL_Renderer * GetRawHandle();
    void ClearTexture(const SDL_Color& color, SDLTexture& texture);

private:
    std::unique_ptr<SDL_Renderer, sdl_deleter> renderer_handle;
    std::shared_ptr<SDLWindow> sdlWindow;
};

