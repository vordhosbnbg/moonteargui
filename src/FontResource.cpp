#include "FontResource.h"
using namespace std;

FontResource::FontResource(string path, int ptSize) : Resource(path), size(ptSize)
{
}

FontResource::~FontResource()
{
}

void FontResource::Load()
{
    font = make_shared<TTFFont>(path_to_resource, size);
}

TTF_Font * FontResource::GetFontHandle()
{
    return font->GetRawHandle();
}
