#include "SDLTexture.h"


SDLTexture::SDLTexture(std::shared_ptr<SDLRenderer>& renderer, std::shared_ptr<SDLSurface> surface) :
    texture_handle(SDL_CreateTextureFromSurface(renderer->GetRawHandle(), surface->GetRawHandle()), sdl_deleter())
{
    sdlRenderer = renderer;
}

SDLTexture::SDLTexture(std::shared_ptr<SDLRenderer>& renderer, int w, int h)
{
    SDL_CreateTexture(renderer->GetRawHandle(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    sdlRenderer = renderer;
}



SDL_Texture * SDLTexture::GetRawHandle()
{
    return texture_handle.get();
}

int SDLTexture::GetWidth()
{
    int retVal = 0;

    SDL_QueryTexture(texture_handle.get(), nullptr, nullptr, &retVal, nullptr);
    
    return retVal;
}

int SDLTexture::GetHeight()
{
    int retVal = 0;

    SDL_QueryTexture(texture_handle.get(), nullptr, nullptr, nullptr, &retVal);

    return retVal;
}

