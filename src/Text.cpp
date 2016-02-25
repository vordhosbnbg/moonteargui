#include "Text.h"
#include "SDL_ttf.h"

#define DEFAULT_PT_SIZE 18
using namespace std;
Text::Text(shared_ptr<TextResource> defaultText, shared_ptr<FontResource> defaultFont) : sizePt(DEFAULT_PT_SIZE)
{
    textRes = defaultText;
    fontRes = defaultFont;
}

Text::~Text()
{
}

void Text::SetSizePt(int size)
{
    sizePt = size;
    cached = false;
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
    SDL_Color foreground_color = {0xFF, 0xFF, 0xFF, 0};
    SDL_Color background_color = {0x00, 0x00, 0x00, 0};
    TTF_Font * font_handle = fontRes->GetFontHandle();
    TTF_SetFontStyle(font_handle, renderstyle);
    TTF_SetFontOutline(font_handle, outline);
    TTF_SetFontKerning(font_handle, kerning);
    TTF_SetFontHinting(font_handle, hinting);
    shared_ptr<SDLSurface> surface = make_shared<SDLSurface>(TTF_RenderText_Shaded(font_handle, textRes->GetString().c_str(), foreground_color, background_color));
    sdlTexture = make_shared<SDLTexture>(sdlRenderer, surface);
    int width = sdlTexture->GetWidth();
    int height = sdlTexture->GetHeight();
    SetW(width);
    SetH(height);
    srcRect.SetW(width);
    srcRect.SetH(height);

    cached = true;
}
