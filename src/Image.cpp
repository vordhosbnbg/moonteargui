#include "Image.h"
using namespace std;

Image::Image(shared_ptr<BitmapResource> defaultBitmap) : autosize(true)
{
    bitmap = defaultBitmap;
}

Image::~Image()
{
}

void Image::SetBitmap(shared_ptr<BitmapResource> defaultBitmap)
{
    lock_guard<mutex> lock(mxWidget);
    bitmap = defaultBitmap;
    cached = false;
}

void Image::OnRegisterRenderer()
{
    RenderImage();
}

void Image::Draw()
{
    lock_guard<mutex> lock(mxWidget);
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
    sdlTexture = make_shared<SDLTexture>(sdlRenderer, bitmap->GetSurface());
    cached = true;
}
