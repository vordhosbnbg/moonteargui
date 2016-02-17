#include "TextureManager.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

shared_ptr<SDLTexture> TextureManager::GetTexture(string filename)
{
    shared_ptr<SDLTexture> retVal = nullptr;
    if (mapOfTextures.find(filename) != mapOfTextures.end()) 
    {
        retVal = mapOfTextures.at(filename);
    }
    else 
    {
        retVal = LoadTexture(filename);
        if (retVal) 
        {
            mapOfTextures.insert(pair<string, shared_ptr<SDLTexture>>(filename, retVal));
        }
    }

    return retVal;
}

shared_ptr<SDLTexture> TextureManager::LoadTexture(string filename)
{
    return shared_ptr<SDLTexture>();
}
