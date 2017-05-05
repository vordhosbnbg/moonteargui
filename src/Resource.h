#pragma once

#include <string>
#include "ResourceTypes.h"
#include "ResourceManager.h"

class Resource 
{
public:
    Resource(std::string path);
    ~Resource();

    virtual void Load();
    virtual void Save();
protected:

    std::string path_to_resource;
};

