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

    virtual void OnRegisterRenderer();
    virtual void Draw();
protected:

    void RenderText();

    int sizePt;
    std::shared_ptr<TextResource> textRes;
    std::shared_ptr<FontResource> fontRes;
    std::shared_ptr<SDLTexture> sdlTexture;
    SDL_Color fgColor;
    SDL_Color bgColor;
};



#endif // TEXT_H
