#pragma once

#include "Widget.h"
#include "TextResource.h"
#include "FontResource.h"

class Text : public Widget
{
public:
    Text(std::shared_ptr<TextResource> defaultText, std::shared_ptr<FontResource> defaultFont);
    ~Text() override = default;

    void SetTextResource(std::shared_ptr<TextResource> text);
    std::shared_ptr<TextResource> GetTextResource();

    void SetText(const std::string& text);
    void AppendText(const std::string& text);
    std::string GetText();

    void SetFont(std::shared_ptr<FontResource> font);
    std::shared_ptr<FontResource> GetFont();

    void SetSizePt(int size);
    int GetSizePt();

    void SetFGColor(SDL_Color col);
    SDL_Color GetFGColor();

    void SetBGColor(SDL_Color col);
    SDL_Color GetBGColor();

    void SetTransparent(bool val);
    bool IsTransparent();

    void SetReadOnly(bool val);
    bool IsReadOnly();

    void Draw() override;
    void ProcessEvent(const SDL_Event& ev) override;
protected:

    void OnRegisterRenderer() override;
    void SyncInternalBuffer();
    void DeleteLastCharacter();
    void InsertNewLineCharacter();
    void RenderText();
    std::string GetRenderedText();

    int sizePt;
    std::string internalTextBuffer;
    std::shared_ptr<TextResource> textRes;
    std::shared_ptr<FontResource> fontRes;
    std::shared_ptr<SDLTexture> sdlTextureBackground;
    std::shared_ptr<SDLTexture> sdlTextureText;
    SDL_Color fgColor;
    SDL_Color bgColor;
    SDL_Color boxColor{255,255,255,255};
    bool boxed{true};
    bool transparent;
    bool readOnly;
    bool useTextResource;
    SDLRect srcTextRect;
    SDLFRect dstTextRect;
    SDLRect srcBgRect;
    SDLFRect dstBgRect;
};
