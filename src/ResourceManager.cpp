#include "ResourceManager.h"
using namespace std;

ResourceManager::ResourceManager() : textureManager(make_shared<TextureManager>())
{

}

ResourceManager::~ResourceManager()
{
}

shared_ptr<SDLTexture> ResourceManager::GetTexture(string filename)
{
    return textureManager->GetTexture(filename);
}
