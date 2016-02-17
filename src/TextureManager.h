#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <memory>
#include <map>
#include <string>
#include "SDLTexture.h"

using namespace std;
class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    shared_ptr<SDLTexture> GetTexture(string filename);

private:
    shared_ptr<SDLTexture> LoadTexture(string filename);
    map<string, shared_ptr<SDLTexture>> mapOfTextures;
};
#endif // TEXTUREMANAGER_H
