#pragma once

#include <memory>
#include <map>
#include <string>
#include "SDLTexture.h"

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    std::shared_ptr<SDLTexture> GetTexture(const std::string& filename);

private:
    std::shared_ptr<SDLTexture> LoadTexture(const std::string& filename);
    std::map<std::string, std::shared_ptr<SDLTexture>> mapOfTextures;
};
