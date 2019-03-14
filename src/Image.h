#pragma once

#include "Widget.h"
#include "BitmapResource.h"

class Image : public Widget
{
public:
    Image(std::shared_ptr<BitmapResource>& defaultBitmap);
    ~Image() override=default;

    void SetBitmap(const std::shared_ptr<BitmapResource>& defaultBitmap);

    void Draw() override;

private:
    void OnRegisterRenderer() override;
    void RenderImage();
    std::shared_ptr<BitmapResource> bitmap;
    std::shared_ptr<SDLTexture> sdlTexture;
    SDLRect srcImgRect;
    SDLRect dstImgRect;
    bool autosize;
    bool doAutosize;
};

