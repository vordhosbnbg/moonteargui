#pragma once

#include "TextureManager.h"

class ResourceManager 
{
public:
    ResourceManager();
    ~ResourceManager();

    std::shared_ptr<SDLTexture> GetTexture(const std::string& filename);

private:
    std::shared_ptr<TextureManager> textureManager;
};

