#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <memory>
#include <map>
#include <string>
#include "SDLTexture.h"

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    std::shared_ptr<SDLTexture> GetTexture(std::string filename);

private:
    std::shared_ptr<SDLTexture> LoadTexture(std::string filename);
    std::map<std::string, std::shared_ptr<SDLTexture>> mapOfTextures;
};
#endif // TEXTUREMANAGER_H
