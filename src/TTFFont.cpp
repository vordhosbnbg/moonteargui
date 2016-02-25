#include "TTFFont.h"

TTFFont::TTFFont(std::string filename, int sizePt) : font_handle(TTF_OpenFont(filename.c_str(), sizePt))
{
}

TTFFont::~TTFFont()
{
}

TTF_Font * TTFFont::GetRawHandle()
{
    return font_handle.get();
}
