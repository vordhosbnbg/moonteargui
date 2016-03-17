#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H
#include <functional>
#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "Widget.h"

class RootWindow 
{
public:
    RootWindow(std::shared_ptr<SDLWindow> window);
    ~RootWindow();
    void ProcessEvent(SDL_Event ev);
    void Render();
    void AddWidget(std::shared_ptr<Widget> widget);
    unsigned int GetWindowID();
private:

    enum TraverseType
    {
        Drawing,
        EventProcessing
    };

    void TraverseWidgets(TraverseType ttype);


    std::shared_ptr<Widget> rootWidget;
    std::shared_ptr<SDLWindow> sdlWindow;
    std::shared_ptr<SDLRenderer> sdlRenderer;

    int widgetCount;
    SDL_Event currentEvent;
    bool visible;
};

#endif // ROOTWINDOW_H
