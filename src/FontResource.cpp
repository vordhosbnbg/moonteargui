#include "FontResource.h"


FontResource::FontResource(const std::string& path, int ptSize) : Resource(path), size(ptSize)
{
}

FontResource::~FontResource()
{
}

void FontResource::Load()
{
    font = std::make_shared<TTFFont>(path_to_resource, size);
}

TTF_Font * FontResource::GetFontHandle()
{
    if(font)
        return font->GetRawHandle();

    return nullptr;
}

int FontResource::GetSize() const
{
    return size;
}
