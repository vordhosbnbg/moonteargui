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

    void SetText(std::shared_ptr<TextResource> text);
    std::shared_ptr<TextResource> GetText();

    void SetFont(std::shared_ptr<FontResource> font);
    std::shared_ptr<FontResource> GetFont();

    void SetSizePt(int size);
    int GetSizePt();

    void SetFGColor(SDL_Color col);
    SDL_Color GetFGColor();

    void SetBGColor(SDL_Color col);
    SDL_Color GetBGColor();

    void SetTransparent(bool val);
    bool GetTransparent();

    virtual void Draw();
protected:

    virtual void OnRegisterRenderer();
    void RenderText();

    int sizePt;
    std::shared_ptr<TextResource> textRes;
    std::shared_ptr<FontResource> fontRes;
    std::shared_ptr<SDLTexture> sdlTextureBackground;
    std::shared_ptr<SDLTexture> sdlTextureText;
    SDL_Color fgColor;
    SDL_Color bgColor;
    bool transparent;
};



#endif // TEXT_H
