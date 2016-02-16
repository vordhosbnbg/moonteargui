#include "SDLTexture.h"

SDLTexture::SDLTexture(shared_ptr<SDLRenderer> renderer, shared_ptr<SDLSurface> surface) : texture_handle(SDL_CreateTextureFromSurface(renderer->GetRawHandle(), surface->GetRawHandle()), sdl_deleter())
{
}

SDLTexture::~SDLTexture()
{
}
