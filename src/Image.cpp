#include "Image.h"
using namespace std;

Image::Image(shared_ptr<BitmapResource> defaultBitmap)
{
    bitmap = defaultBitmap;
}

Image::~Image()
{
}

void Image::SetBitmap(shared_ptr<BitmapResource> defaultBitmap)
{
    bitmap = defaultBitmap;
    cached = false;
}

void Image::OnRegisterRenderer()
{
    RenderImage();
}

void Image::Draw()
{
    if (sdlRenderer) 
    {
        if (!cached) 
        {
            RenderImage();
        }
        sdlRenderer->Draw(sdlTexture, srcRect, dstRect);
    }
}

void Image::RenderImage()
{
    sdlTexture = make_shared<SDLTexture>(sdlRenderer, bitmap->GetSurface());
    if (sdlTexture)
    {
        int width = sdlTexture->GetWidth();
        int height = sdlTexture->GetHeight();
        SetW(width);
        SetH(height);
        srcRect.SetW(width);
        srcRect.SetH(height);
        cached = true;
    }
}
