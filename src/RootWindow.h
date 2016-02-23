#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H
#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "Widget.h"

class RootWindow 
{
public:
    RootWindow(std::shared_ptr<SDLWindow> window);
    ~RootWindow();
    void Render();
    void AddWidget(std::shared_ptr<Widget> widget);
private:
    void TraverseWidgets();


    std::shared_ptr<Widget> rootWidget;
    std::shared_ptr<SDLWindow> sdlWindow;
    std::shared_ptr<SDLRenderer> sdlRenderer;

    int widgetCount;
};

#endif // ROOTWINDOW_H
