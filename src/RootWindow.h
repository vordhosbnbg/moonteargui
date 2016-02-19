#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H
#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "Widget.h"

class RootWindow 
{
public:
    RootWindow(shared_ptr<SDLWindow> window);
    ~RootWindow();
    void Render();
    void AddWidget(shared_ptr<Widget> widget);
private:
    void TraverseWidgets();


    shared_ptr<Widget> rootWidget;
    shared_ptr<SDLWindow> sdlWindow;
    shared_ptr<SDLRenderer> sdlRenderer;

    int widgetCount;
};

#endif // ROOTWINDOW_H
