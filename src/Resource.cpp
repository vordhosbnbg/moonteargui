#include "Resource.h"


Resource::Resource(const std::string& path) : path_to_resource(path)
{
}

Resource::~Resource()
{
}

void Resource::Load()
{
}

void Resource::Save()
{

}

std::string& Resource::getFilePath()
{
    return path_to_resource;
}
