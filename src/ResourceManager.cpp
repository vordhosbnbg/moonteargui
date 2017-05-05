#include "ResourceManager.h"


ResourceManager::ResourceManager() : textureManager(std::make_shared<TextureManager>())
{

}

ResourceManager::~ResourceManager()
{
}

std::shared_ptr<SDLTexture> ResourceManager::GetTexture(std::string filename)
{
    return textureManager->GetTexture(filename);
}
