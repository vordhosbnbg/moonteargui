#ifndef IMAGE_H
#define IMAGE_H

#include "Widget.h"
#include "BitmapResource.h"

class Image : public Widget
{
public:
    Image(shared_ptr<BitmapResource> defaultBitmap);
    ~Image();

    void SetBitmap(shared_ptr<BitmapResource> defaultBitmap);
    virtual void OnRegisterRenderer();

    virtual void Draw();

private:
    shared_ptr<BitmapResource> bitmap;
    shared_ptr<SDLTexture> sdlTexture;
};

#endif // IMAGE_H
