#include "Text.h"
#include "SDL2/SDL_ttf.h"

#define DEFAULT_PT_SIZE 18
using namespace std;
Text::Text(shared_ptr<TextResource> defaultText, shared_ptr<FontResource> defaultFont) : sizePt(DEFAULT_PT_SIZE), fgColor({0xFF, 0xFF, 0xFF, 0xFF}), bgColor({ 0x00, 0x00, 0x00, 0x00 }), transparent(false), readOnly(true), useTextResource(true)
{
    textRes = defaultText;
    fontRes = defaultFont;
}

Text::~Text()
{
}

void Text::SetTextResource(std::shared_ptr<TextResource> text)
{
    lock_guard<mutex> lock(mxWidget);
    textRes = text;
    cached = false;
    useTextResource = true;
    internalTextBuffer = text->GetString();
}

std::shared_ptr<TextResource> Text::GetTextResource()
{
    lock_guard<mutex> lock(mxWidget);
    return textRes;
}

void Text::SetText(std::string text)
{
    internalTextBuffer = text;
    cached = false;
    useTextResource = false;
}

void Text::AppendText(std::string text)
{
    cached = false;
    if (useTextResource) 
    {
        internalTextBuffer = textRes->GetString();
    }
    useTextResource = false;
    internalTextBuffer.append(text);
}

std::string Text::GetText()
{
    string retVal;
    if (useTextResource) 
    {
        retVal = textRes->GetString();
    }
    else 
    {
        retVal = internalTextBuffer;
    }
    return retVal;
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

bool Text::IsTransparent()
{
    return transparent;
}

void Text::SetReadOnly(bool val)
{
    readOnly = val;
}

bool Text::IsReadOnly()
{
    return readOnly;
}

void Text::OnRegisterRenderer()
{
    RenderText();
}

void Text::SyncInternalBuffer()
{
    if (useTextResource)
    {
        internalTextBuffer = textRes->GetString();
        useTextResource = false;
    }
}

void Text::DeleteLastCharacter()
{
    SyncInternalBuffer();
    if (internalTextBuffer.size() > 0)
    {
        internalTextBuffer.pop_back();
        cached = false;
    }
}

void Text::InsertNewLineCharacter()
{
    SyncInternalBuffer();
    internalTextBuffer.push_back('\n');
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
        dstTextRect.SetX(GetX());
        dstTextRect.SetY(GetY());
        dstBgRect.SetX(GetX());
        dstBgRect.SetY(GetY());
        if ((!transparent) && (sdlTextureBackground))
        {
            sdlRenderer->Draw(sdlTextureBackground, srcBgRect, dstBgRect);
        }
        if (sdlTextureText) 
        {
            sdlRenderer->Draw(sdlTextureText, srcTextRect, dstTextRect);
        }
    }
}

void Text::ProcessEvent(SDL_Event ev)
{
    switch (ev.type)
    {
        case SDL_TEXTINPUT :
            AppendText(ev.text.text);
            break;
        case SDL_KEYDOWN:
            switch (ev.key.keysym.sym)
            {
            case SDLK_BACKSPACE:
            case SDLK_KP_BACKSPACE:
                DeleteLastCharacter();
                break;
            case SDLK_RETURN:
            case SDLK_KP_ENTER:
                InsertNewLineCharacter();
                break;
            default:
                break;
            }
            break;
        default:
            break;
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
        string renderedText = GetRenderedText();

        shared_ptr<SDLSurface> surfaceText = make_shared<SDLSurface>(TTF_RenderUTF8_Blended(font_handle, renderedText.c_str(), fgColor));
        sdlTextureText = make_shared<SDLTexture>(sdlRenderer, surfaceText);
        if (!transparent)
        {
            shared_ptr<SDLSurface> surfaceBackground = make_shared<SDLSurface>(SDL_CreateRGBSurface(0, GetW(), GetH(), 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000));
            surfaceBackground->SetBlendMode(SDL_BLENDMODE_BLEND);
            surfaceBackground->Fill(bgColor);
            sdlTextureBackground = make_shared<SDLTexture>(sdlRenderer, surfaceBackground);
        }
        srcBgRect.SetW(GetW());
        srcBgRect.SetH(GetH());
        dstBgRect.SetW(GetW());
        dstBgRect.SetH(GetH());

        int width = sdlTextureText->GetWidth();
        int height = sdlTextureText->GetHeight();
        if (width <= GetW())
        {
            dstTextRect.SetW(width);
        }
        else 
        {
            dstTextRect.SetW(GetW());
        }
        dstTextRect.SetH(height);
        srcTextRect.SetW(GetW());
        srcTextRect.SetH(GetH());
        cached = true;
    }
}

string Text::GetRenderedText()
{
    string retVal = GetText();
    int textWidth = 0;
    int textHeight = 0;
    bool searchUp = false;
    bool finished = false;
    TTF_Font * font_handle = fontRes->GetFontHandle();
    size_t charCount = retVal.size();
    size_t searchBegin = 0;
    size_t searchEnd = charCount;
    size_t middle;

    TTF_SizeUTF8(font_handle, retVal.c_str(), &textWidth, &textHeight);
    if (textWidth < GetW())
    {
        finished = true;
    }

    while(!finished)
    {
        middle = searchBegin + (searchEnd - searchBegin) / 2;
        TTF_SizeUTF8(font_handle, retVal.substr(0,middle).c_str(), &textWidth, &textHeight);
        if (textWidth < GetW())  // if we "fit" after one binary search iteration
        {
            TTF_SizeUTF8(font_handle, retVal.substr(0, middle+1).c_str(), &textWidth, &textHeight);
            if (textWidth >= GetW()) // if we are one character over the width limit, we are just right
            {
                retVal = retVal.substr(0, middle + 1);
                finished = true;
            }
            else 
            {
                searchBegin = middle; // we should look upper
            }
        }
        else 
        {
            searchEnd = middle; // we should look lower
        }
        if (searchBegin == searchEnd) 
        {
            retVal = retVal.substr(0, searchBegin);
            finished = true;
        }
    } 


    return retVal;
}
