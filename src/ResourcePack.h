#pragma once

#include "Resource.h"

enum class ResID
{
    Bitmap
};

class ResourcePack
{
public:
    ResourcePack();
    ~ResourcePack();

    std::shared_ptr<Resource> GetResource(ResID id);
};
