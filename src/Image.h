#ifndef IMAGE_H
#define IMAGE_H

#include "Widget.h"
#include "SDLTexture.h"

class Image : public Widget
{
public:
    Image();
    ~Image();

    virtual void vDraw();

private:
    shared_ptr<SDLTexture> texture;
};

#endif // IMAGE_H
