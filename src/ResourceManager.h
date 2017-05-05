#pragma once

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

