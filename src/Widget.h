#ifndef WIDGET_H
#define WIDGET_H
#include "SDLRenderer.h"

class Widget
{
public:
    Widget();
    ~Widget();

    void RegisterRenderer(SDLRenderer * rend);
    virtual void OnRegisterRenderer();
    void AttachChild(shared_ptr<Widget> child);
    void AttachSibling(shared_ptr<Widget> sibling);
    shared_ptr<Widget> GetFirstChild();
    shared_ptr<Widget> GetNextSibling();

    void SetX(int x);
    void SetY(int y);
    void SetW(int w);
    void SetH(int h);

    virtual void Draw();


protected:
    SDLRect srcRect;
    SDLRect dstRect;
    SDLRenderer * sdlRenderer;

private:
    shared_ptr<Widget> firstChild;
    shared_ptr<Widget> nextSibling;
};

#endif // WIDGET_H
