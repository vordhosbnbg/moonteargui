#ifndef TEXT_H
#define TEXT_H
#include "Widget.h"
#include "TextResource.h"
#include "FontResource.h"

class Text : public Widget
{
public:
    Text(std::shared_ptr<TextResource> defaultText, std::shared_ptr<FontResource> defaultFont);
    ~Text();

    void SetTextResource(std::shared_ptr<TextResource> text);
    std::shared_ptr<TextResource> GetTextResource();

    void SetText(std::string text);
    void AppendText(std::string text);
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

    virtual void Draw();
    virtual void ProcessEvent(SDL_Event ev);
protected:

    virtual void OnRegisterRenderer();
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
    bool transparent;
    bool readOnly;
    bool useTextResource;
    SDLRect srcTextRect;
    SDLRect dstTextRect;
    SDLRect srcBgRect;
    SDLRect dstBgRect;
};



#endif // TEXT_H
