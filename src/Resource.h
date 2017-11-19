#pragma once

#include <string>
#include "ResourceTypes.h"
#include "ResourceManager.h"

class Resource 
{
public:
    Resource(const std::string& path);
    virtual ~Resource();

    virtual void Load();
    virtual void Save();
protected:

    std::string path_to_resource;
};

