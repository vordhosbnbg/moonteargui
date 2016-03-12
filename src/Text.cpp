#include "Text.h"
#include "SDL_ttf.h"

#define DEFAULT_PT_SIZE 18
using namespace std;
Text::Text(shared_ptr<TextResource> defaultText, shared_ptr<FontResource> defaultFont) : sizePt(DEFAULT_PT_SIZE), fgColor({0xFF, 0xFF, 0xFF, 0xFF}), bgColor({ 0x00, 0x00, 0x00, 0x00 }), transparent(false)
{
    textRes = defaultText;
    fontRes = defaultFont;
}

Text::~Text()
{
}

void Text::SetText(std::shared_ptr<TextResource> text)
{
    lock_guard<mutex> lock(mxWidget);
    textRes = text;
    cached = false;
}

std::shared_ptr<TextResource> Text::GetText()
{
    lock_guard<mutex> lock(mxWidget);
    return textRes;
}

void Text::SetFont(std::shared_ptr<FontResource> font)
{
    lock_guard<mutex> lock(mxWidget);
    fontRes = font;
    cached = false;
}

std::shared_ptr<FontResource> Text::GetFont()
{
    lock_guard<mutex> lock(mxWidget);
    return fontRes;
}

void Text::SetSizePt(int size)
{
    lock_guard<mutex> lock(mxWidget);
    sizePt = size;
    cached = false;
}

int Text::GetSizePt()
{
    lock_guard<mutex> lock(mxWidget);
    return sizePt;
}

void Text::SetFGColor(SDL_Color col)
{
    lock_guard<mutex> lock(mxWidget);
    fgColor = col;
    cached = false;
}

SDL_Color Text::GetFGColor()
{
    lock_guard<mutex> lock(mxWidget);
    return fgColor;
}

void Text::SetBGColor(SDL_Color col)
{
    lock_guard<mutex> lock(mxWidget);
    bgColor = col;
    cached = false;
}

SDL_Color Text::GetBGColor()
{
    lock_guard<mutex> lock(mxWidget);
    return bgColor;
}

void Text::SetTransparent(bool val)
{
    transparent = true;
}

bool Text::GetTransparent()
{
    return transparent;
}

void Text::OnRegisterRenderer()
{
    RenderText();
}

void Text::Draw()
{
    lock_guard<mutex> lock(mxWidget);
    if (sdlRenderer)
    {
        if (!cached)
        {
            RenderText();
        }
        if ((!transparent) && (sdlTextureBackground))
        {
            sdlRenderer->Draw(sdlTextureBackground, srcRect, dstRect);
        }
        if (sdlTextureText) 
        {
            sdlRenderer->Draw(sdlTextureText, srcRect, dstRect);
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
    if (font_handle)
    {
        TTF_SetFontStyle(font_handle, renderstyle);
        TTF_SetFontOutline(font_handle, outline);
        TTF_SetFontKerning(font_handle, kerning);
        TTF_SetFontHinting(font_handle, hinting);
        shared_ptr<SDLSurface> surfaceText = make_shared<SDLSurface>(TTF_RenderText_Blended_Wrapped(font_handle, textRes->GetString().c_str(), fgColor, GetW()));
        sdlTextureText = make_shared<SDLTexture>(sdlRenderer, surfaceText);
        if(!transparent)
        {
            shared_ptr<SDLSurface> surfaceBackground = make_shared<SDLSurface>(SDL_CreateRGBSurface(0, GetW(), GetH(), 32, 0, 0, 0, 0));
            surfaceBackground->Fill(bgColor);
            sdlTextureBackground = make_shared<SDLTexture>(sdlRenderer, surfaceBackground);
        }
        int width = sdlTextureText->GetWidth();
        int height = sdlTextureText->GetHeight();
        dstRect.SetW(width);
        dstRect.SetH(height);
        srcRect.SetW(width);
        srcRect.SetH(height);
        cached = true;
    }
}
