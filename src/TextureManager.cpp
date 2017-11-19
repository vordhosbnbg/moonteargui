#include "TextureManager.h"



TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

std::shared_ptr<SDLTexture> TextureManager::GetTexture(const std::string& filename)
{
    std::shared_ptr<SDLTexture> retVal = nullptr;
    if (mapOfTextures.find(filename) != mapOfTextures.end()) 
    {
        retVal = mapOfTextures.at(filename);
    }
    else 
    {
        retVal = LoadTexture(filename);
        if (retVal) 
        {
            mapOfTextures.insert(std::pair<std::string, std::shared_ptr<SDLTexture>>(filename, retVal));
        }
    }

    return retVal;
}

std::shared_ptr<SDLTexture> TextureManager::LoadTexture(const std::string& filename)
{
    return std::shared_ptr<SDLTexture>();
}
