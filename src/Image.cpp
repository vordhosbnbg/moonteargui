#include "Image.h"


Image::Image(std::shared_ptr<BitmapResource> defaultBitmap) : autosize(true)
{
    bitmap = defaultBitmap;
}

Image::~Image()
{
}

void Image::SetBitmap(std::shared_ptr<BitmapResource> defaultBitmap)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    bitmap = defaultBitmap;
    cached = false;
}

void Image::OnRegisterRenderer()
{
    RenderImage();
}

void Image::Draw()
{
    std::lock_guard<std::mutex> lock(mxWidget);
    if (sdlRenderer)
    {
        if (!cached)
        {
            RenderImage();
        }
        if (sdlTexture)
        {
            int textureWidth = sdlTexture->GetWidth();
            int textureHeight = sdlTexture->GetHeight();
            srcImgRect.SetW(textureWidth);
            srcImgRect.SetH(textureHeight);
            if (autosize)
            {
                widgetWidth = textureWidth;
                widgetHeight = textureHeight;
            }

            dstImgRect.SetX(GetX());
            dstImgRect.SetY(GetY());
            dstImgRect.SetW(GetW());
            dstImgRect.SetH(GetH());
            sdlRenderer->Draw(sdlTexture, srcImgRect, dstImgRect);
        }
    }
}

void Image::RenderImage()
{
    sdlTexture = std::make_shared<SDLTexture>(sdlRenderer, bitmap->GetSurface());
    cached = true;
}
