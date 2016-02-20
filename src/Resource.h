#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include "ResourceTypes.h"
#include "ResourceManager.h"

class Resource 
{
public:
    Resource(string path);
    ~Resource();

    virtual void Load();
protected:

    string path_to_resource;
};

#endif // RESOURCE_H
