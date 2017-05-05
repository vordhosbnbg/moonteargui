#include "BitmapResource.h"



BitmapResource::BitmapResource(std::string path) : Resource(path)
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
    return sdlSurface;
}

