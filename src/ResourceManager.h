#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "TextureManager.h"

class ResourceManager 
{
public:
    ResourceManager();
    ~ResourceManager();

    shared_ptr<SDLTexture> GetTexture(string filename);

private:
    shared_ptr<TextureManager> textureManager;
};

#endif // RESOURCEMANAGER_H
