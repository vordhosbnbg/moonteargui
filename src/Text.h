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

    void SetSizePt(int size);

    virtual void Draw();
protected:

    void RenderText();

    int sizePt;
    std::shared_ptr<TextResource> textRes;
    std::shared_ptr<FontResource> fontRes;
    std::shared_ptr<SDLTexture> sdlTexture;
};



#endif // TEXT_H
