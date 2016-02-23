#ifndef IMAGE_H
#define IMAGE_H

#include "Widget.h"
#include "BitmapResource.h"

class Image : public Widget
{
public:
    Image(std::shared_ptr<BitmapResource> defaultBitmap);
    ~Image();

    void SetBitmap(std::shared_ptr<BitmapResource> defaultBitmap);
    virtual void OnRegisterRenderer();

    virtual void Draw();

private:
    std::shared_ptr<BitmapResource> bitmap;
    std::shared_ptr<SDLTexture> sdlTexture;
};

#endif // IMAGE_H
