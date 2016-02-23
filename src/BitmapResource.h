#ifndef BITMAPRESOURCE_H
#define BITMAPRESOURCE_H
#include <memory>
#include "Resource.h"
#include "SDLTexture.h"

class BitmapResource : public Resource
{
public:
    BitmapResource(std::string path);
    ~BitmapResource();
    
    virtual void Load();

    std::shared_ptr<SDLSurface> GetSurface();

private:
    std::shared_ptr<SDLSurface> sdlSurface;
};

#endif // BITMAPRESOURCE_H
