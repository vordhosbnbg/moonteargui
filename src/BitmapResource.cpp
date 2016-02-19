#include "BitmapResource.h"

BitmapResource::BitmapResource(string filename) : Resource(filename)
{
}

BitmapResource::~BitmapResource()
{
}

void BitmapResource::Load()
{
    sdlSurface = make_shared<SDLSurface>(path_to_resource);
}

shared_ptr<SDLSurface> BitmapResource::GetSurface()
{
    return sdlSurface;
}

