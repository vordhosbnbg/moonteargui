#include "Text.h"
#include "SDL_ttf.h"

#define DEFAULT_PT_SIZE 18
using namespace std;
Text::Text(shared_ptr<TextResource> defaultText, shared_ptr<FontResource> defaultFont) : sizePt(DEFAULT_PT_SIZE), fgColor({0xFF, 0xFF, 0xFF, 0xFF}), bgColor({ 0x00, 0x00, 0x00, 0x00 })
{
    textRes = defaultText;
    fontRes = defaultFont;
}

Text::~Text()
{
}

void Text::SetText(std::shared_ptr<TextResource> text)
{
    textRes = text;
    cached = false;
}

std::shared_ptr<TextResource> Text::GetText()
{
    return textRes;
}

void Text::SetFont(std::shared_ptr<FontResource> font)
{
    fontRes = font;
    cached = false;
}

std::shared_ptr<FontResource> Text::GetFont()
{
    return fontRes;
}

void Text::SetSizePt(int size)
{
    sizePt = size;
    cached = false;
}

int Text::GetSizePt()
{
    return sizePt;
}

void Text::SetFGColor(SDL_Color col)
{
    fgColor = col;
    cached = false;
}

SDL_Color Text::GetFGColor()
{
    return fgColor;
}

void Text::SetBGColor(SDL_Color col)
{
    bgColor = col;
    cached = false;
}

SDL_Color Text::GetBGColor()
{
    return bgColor;
}

void Text::OnRegisterRenderer()
{
    RenderText();
}

void Text::Draw()
{
    if (sdlRenderer) 
    {
        if (!cached)
        {
            RenderText();
        }
        if (sdlTexture) 
        {
            sdlRenderer->Draw(sdlTexture, srcRect, dstRect);
        }
    }
}

void Text::RenderText()
{
    int renderstyle = TTF_STYLE_NORMAL;
    int outline = 0;
    int hinting = TTF_HINTING_NORMAL;
    int kerning = 1;
    TTF_Font * font_handle = fontRes->GetFontHandle();
    TTF_SetFontStyle(font_handle, renderstyle);
    TTF_SetFontOutline(font_handle, outline);
    TTF_SetFontKerning(font_handle, kerning);
    TTF_SetFontHinting(font_handle, hinting);
    shared_ptr<SDLSurface> surface = make_shared<SDLSurface>(TTF_RenderText_Shaded(font_handle, textRes->GetString().c_str(), fgColor, bgColor));
    sdlTexture = make_shared<SDLTexture>(sdlRenderer, surface);
    int width = sdlTexture->GetWidth();
    int height = sdlTexture->GetHeight();
    SetW(width);
    SetH(height);
    srcRect.SetW(width);
    srcRect.SetH(height);

    cached = true;
}
