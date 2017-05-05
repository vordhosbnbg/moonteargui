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
            int width = sdlTexture->GetWidth();
            int height = sdlTexture->GetHeight();
            srcImgRect.SetW(width);
            srcImgRect.SetH(height);
            if (autosize)
            {
                dstImgRect.SetW(width);
                dstImgRect.SetH(height);
            }

            dstImgRect.SetX(GetX());
            dstImgRect.SetY(GetY());
            sdlRenderer->Draw(sdlTexture, srcImgRect, dstImgRect);
        }
    }
}

void Image::RenderImage()
{
    sdlTexture = std::make_shared<SDLTexture>(sdlRenderer, bitmap->GetSurface());
    cached = true;
}
