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

}

void Image::OnRegisterRenderer()
{
    sdlTexture = make_shared<SDLTexture>(sdlRenderer, bitmap->GetSurface());
    if (sdlTexture)
    {
        int width = sdlTexture->GetWidth();
        int height = sdlTexture->GetHeight();
        dstRect.SetW(width);
        dstRect.SetH(height);
        srcRect.SetW(width);
        srcRect.SetH(height);
    }
}

void Image::Draw()
{
    if (sdlTexture && sdlRenderer) 
    {
        sdlRenderer->Draw(sdlTexture, srcRect, dstRect);
    }
}
