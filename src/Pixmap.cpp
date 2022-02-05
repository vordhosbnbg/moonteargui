#include "Pixmap.h"


void Pixmap::saveToPNG(const char* filename)
{
    std::lock_guard lock(mxTexture);
    SDLSurface surface = sdlRenderer->getSurfaceFromTexture(*pixmapTexture.get());
    surface.SaveToPNG(filename);
}

void Pixmap::Draw()
{
    std::lock_guard lock(mxTexture);

    if(!cached)
    {
        RenderPixmapToTexture();
    }
    if(pixmapTexture)
    {
        srcRect.SetH(GetH());
        srcRect.SetW(GetW());

        dstRect.SetX(GetX());
        dstRect.SetY(GetY());
        dstRect.SetH(GetH());
        dstRect.SetW(GetW());
        sdlRenderer->DrawF(*pixmapTexture.get(), srcRect, dstRect, rotationAngle);
    }

}

void Pixmap::ProcessEvent(const SDL_Event& ev)
{

}

void Pixmap::resizeBuffer()
{
    pointBuffer.resize(pixmapWidth * pixmapHeight, {0, 0, 0, SDL_ALPHA_OPAQUE});
}

void Pixmap::RenderPixmapToTexture()
{
    if(!pixmapTexture)
    {
        pixmapTexture = std::make_shared<SDLTexture>(sdlRenderer, GetW(), GetH());
    }
    else
    {
        pixmapTexture->Clear(bgColor);
    }

    sdlRenderer->DrawPointsOnTexture(*pixmapTexture.get(), pixmapWidth, pixmapHeight, pointBuffer);

    cached = true;
}
