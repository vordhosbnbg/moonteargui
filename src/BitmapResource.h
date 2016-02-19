#ifndef BITMAPRESOURCE_H
#define BITMAPRESOURCE_H
#include <memory>
#include "Resource.h"
#include "SDLTexture.h"

class BitmapResource : public Resource
{
public:
    BitmapResource(string filename);
    ~BitmapResource();
    
    virtual void Load();

    shared_ptr<SDLSurface> GetSurface();

private:
    shared_ptr<SDLSurface> sdlSurface;
};

#endif // BITMAPRESOURCE_H
