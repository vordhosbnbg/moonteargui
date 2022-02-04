#include "Pixmap.h"


void Pixmap::Draw()
{

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
    pointBuffer.resize(pixmapWidth * pixmapHeight, {0, 0, 0, 255});
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

    sdlRenderer->DrawPointsOnTextureF(*pixmapTexture.get(), 0, 0, pixmapWidth, pixmapHeight, pointBuffer);

    cached = true;
}
