#include "SDLTexture.h"


SDLTexture::SDLTexture(std::shared_ptr<SDLRenderer> renderer, std::shared_ptr<SDLSurface> surface) : texture_handle(SDL_CreateTextureFromSurface(renderer->GetRawHandle(), surface->GetRawHandle()), sdl_deleter())
{
    sdlRenderer = renderer;
}

SDLTexture::~SDLTexture()
{
}

SDL_Texture * SDLTexture::GetRawHandle()
{
    return texture_handle.get();
}

int SDLTexture::GetWidth()
{
    int retVal = 0;

    SDL_QueryTexture(texture_handle.get(), NULL, NULL, &retVal, NULL);
    
    return retVal;
}

int SDLTexture::GetHeight()
{
    int retVal = 0;

    SDL_QueryTexture(texture_handle.get(), NULL, NULL, NULL, &retVal);

    return retVal;
}

