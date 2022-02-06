#pragma once

#include <memory>
#include "SDL.h"
#include "SDLDeleter.h"
#include "SDLRenderer.h"
#include "SDLSurface.h"

class SDLRenderer;
class SDLTexture
{
public:
    SDLTexture(std::shared_ptr<SDLRenderer>& renderer, std::shared_ptr<SDLSurface> surface);
    SDLTexture(std::shared_ptr<SDLRenderer>& renderer, int w, int h, SDL_TextureAccess access = SDL_TEXTUREACCESS_TARGET);
    ~SDLTexture() = default;

    SDL_Texture * GetRawHandle();
    const SDL_Texture * GetRawHandle() const;
    int GetWidth();
    int GetHeight();
    void Clear(const SDL_Color& bgColor);
    void CopyPixelData(const std::vector<SDL_Color>& sourcePixels);

    SDL_TextureAccess getAccess();
    uint32_t getFormatEnum();
    SDL_PixelFormat* getFormat();

    bool Lock();
    void Unlock();

private:
    void * pixels;
    int pitch;
    std::unique_ptr<SDL_Texture, sdl_deleter> texture_handle;
    std::shared_ptr<SDLRenderer> sdlRenderer; // keep renderer alive, while texture is alive
};
