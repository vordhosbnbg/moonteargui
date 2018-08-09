#pragma once

#include <memory>
#include "Resource.h"
#include "TTFFont.h"


class FontResource : public Resource 
{
public:
    FontResource(const std::string& path, int ptSize);
    ~FontResource();

    virtual void Load();
    TTF_Font * GetFontHandle();
    int GetSize() const;
protected:
    std::shared_ptr<TTFFont> font;
    int size;
};
