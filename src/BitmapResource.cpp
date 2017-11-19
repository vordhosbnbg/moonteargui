#include "BitmapResource.h"



BitmapResource::BitmapResource(const std::string& path) : Resource(path), sdlSurface(nullptr)
{
}

BitmapResource::~BitmapResource()
{
}

void BitmapResource::Load()
{
    sdlSurface = std::make_shared<SDLSurface>(path_to_resource);
}

std::shared_ptr<SDLSurface> BitmapResource::GetSurface()
{
    if(sdlSurface == nullptr)
    {
        Load();
    }
    return sdlSurface;
}

