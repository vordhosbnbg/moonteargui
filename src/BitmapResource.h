#pragma once

#include <memory>
#include "Resource.h"
#include "SDLTexture.h"

class BitmapResource : public Resource
{
public:
    BitmapResource(const std::string& path);
    virtual ~BitmapResource();
    
    virtual void Load();

    std::shared_ptr<SDLSurface> GetSurface();

private:
    std::shared_ptr<SDLSurface> sdlSurface;
};
