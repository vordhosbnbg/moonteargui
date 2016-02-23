#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "TextureManager.h"

class ResourceManager 
{
public:
    ResourceManager();
    ~ResourceManager();

    std::shared_ptr<SDLTexture> GetTexture(std::string filename);

private:
    std::shared_ptr<TextureManager> textureManager;
};

#endif // RESOURCEMANAGER_H
