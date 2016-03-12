#ifndef WIDGET_H
#define WIDGET_H
#include <mutex>
#include "SDLRenderer.h"

class Widget
{
public:
    Widget();
    ~Widget();

    void RegisterRenderer(std::shared_ptr<SDLRenderer> rend);
    void AttachChild(std::shared_ptr<Widget> child);
    void AttachSibling(std::shared_ptr<Widget> sibling);
    std::shared_ptr<Widget> GetFirstChild();
    std::shared_ptr<Widget> GetNextSibling();

    void SetX(int x);
    void SetY(int y);
    void SetW(int w);
    void SetH(int h);
    int GetX();
    int GetY();
    int GetW();
    int GetH();

    virtual void Draw();


protected:
    virtual void OnRegisterRenderer();
    SDLRect srcRect;
    SDLRect dstRect;
    std::shared_ptr<SDLRenderer> sdlRenderer;
    bool cached;
    std::mutex mxWidget;

private:
    std::shared_ptr<Widget> firstChild;
    std::shared_ptr<Widget> nextSibling;
};

#endif // WIDGET_H
