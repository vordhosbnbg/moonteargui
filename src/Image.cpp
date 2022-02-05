#include <iostream>
#include "Image.h"
#include "utils.h"


Image::Image(std::shared_ptr<BitmapResource>& defaultBitmap) : autosize(true), doAutosize(true)
{
    bitmap = defaultBitmap;
}


void Image::SetBitmap(const std::shared_ptr<BitmapResource>& defaultBitmap)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    bitmap = defaultBitmap;
    cached = false;
    if(autosize)
    {
        doAutosize = true;
    }
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
            std::lock_guard lock(mxTexture);
            int textureWidth = sdlTexture->GetWidth();
            int textureHeight = sdlTexture->GetHeight();
            srcImgRect.SetW(textureWidth);
            srcImgRect.SetH(textureHeight);
            if (doAutosize)
            {
                doAutosize = false;
                widgetWidth = textureWidth;
                widgetHeight = textureHeight;
            }

            dstImgRect.SetX(GetX());
            dstImgRect.SetY(GetY());
            dstImgRect.SetW(GetW());
            dstImgRect.SetH(GetH());
            DBGPRINT("Image::Draw() - dstImgRect:("
                      << dstImgRect.GetX() << ","
                      << dstImgRect.GetY() << ","
                      << dstImgRect.GetW() << ","
                      << dstImgRect.GetH() << ")" << std::endl);
            sdlRenderer->DrawF(*sdlTexture.get(), srcImgRect, dstImgRect, rotationAngle);
        }
    }
}

void Image::RenderImage()
{
    std::lock_guard lock(mxTexture);
    sdlTexture = std::make_shared<SDLTexture>(sdlRenderer, bitmap->GetSurface());
    cached = true;
}
