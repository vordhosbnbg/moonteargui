#include <cstring>
#include "SDLTexture.h"


SDLTexture::SDLTexture(std::shared_ptr<SDLRenderer>& renderer, std::shared_ptr<SDLSurface> surface) :
    texture_handle(SDL_CreateTextureFromSurface(renderer->GetRawHandle(), surface->GetRawHandle()), sdl_deleter()),
    sdlRenderer(renderer)
{
}

SDLTexture::SDLTexture(std::shared_ptr<SDLRenderer>& renderer, int w, int h, SDL_TextureAccess access) :
    texture_handle(SDL_CreateTexture(renderer->GetRawHandle(), SDL_PIXELFORMAT_RGBA8888, access, w, h)),
    sdlRenderer(renderer)
{
}



SDL_Texture * SDLTexture::GetRawHandle()
{
    return texture_handle.get();
}

const SDL_Texture * SDLTexture::GetRawHandle() const
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

void SDLTexture::Clear(const SDL_Color& bgColor)
{
    SDL_TextureAccess access = getAccess();
    if(access == SDL_TEXTUREACCESS_TARGET)
    {
        sdlRenderer->ClearTexture(bgColor, *this);
    }
    else if(access == SDL_TEXTUREACCESS_STREAMING)
    {
        uint32_t * pixelData = static_cast<uint32_t*>(pixels);
        int h = GetHeight();
        SDL_PixelFormat* pixFmt = getFormat();
        uint32_t col = SDL_MapRGBA(pixFmt, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        int size = h * pitch / pixFmt->BytesPerPixel;
        for(int idx = 0; idx < size; ++idx)
        {
            pixelData[idx] = col;
        }
    }
}

void SDLTexture::CopyPixelData(const std::vector<SDL_Color>& sourcePixels)
{
    int w;
    int h;
    uint32_t fmtEnum;
    int accessRaw;
    SDL_QueryTexture(texture_handle.get(), &fmtEnum, &accessRaw, &w, &h);
    SDL_TextureAccess access = static_cast<SDL_TextureAccess>(accessRaw);
    SDL_PixelFormat * pixFmt = SDL_AllocFormat(fmtEnum);
    size_t texSize = w * h;
    if(access == SDL_TEXTUREACCESS_STREAMING)
    {
        Lock();
        if(sourcePixels.size() == texSize)
        {
            unsigned char bpp = pixFmt->BytesPerPixel;
            for(int x = 0; x < w; ++x)
            {
                for(int y = 0; y < h; ++y)
                {
                    const SDL_Color& c = sourcePixels[y*w+x];
                    uint32_t pixColor = SDL_MapRGBA(pixFmt, c.r, c.g, c.b, c.a);
                    uint32_t * targetPixel = (uint32_t *)((uint8_t *)pixels + y * pitch + x*bpp);
                    *targetPixel = pixColor;
                }
            }

        }
    }
}

SDL_TextureAccess SDLTexture::getAccess()
{
    int access;
    SDL_QueryTexture(texture_handle.get(), nullptr, &access, nullptr, nullptr);

    return static_cast<SDL_TextureAccess>(access);
}

uint32_t SDLTexture::getFormatEnum()
{
    uint32_t format;
    SDL_QueryTexture(texture_handle.get(), &format, nullptr, nullptr, nullptr);
    return format;
}

SDL_PixelFormat* SDLTexture::getFormat()
{
    return SDL_AllocFormat(getFormatEnum());
}

bool SDLTexture::Lock()
{
    if(SDL_LockTexture(texture_handle.get(), nullptr, &pixels, &pitch))
        return false;

    return true;
}

void SDLTexture::Unlock()
{
    SDL_UnlockTexture(texture_handle.get());
}

