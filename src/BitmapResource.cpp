#include "BitmapResource.h"
using namespace std;


BitmapResource::BitmapResource(string path) : Resource(path)
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

