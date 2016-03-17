#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H
#include <functional>
#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "Widget.h"

class RootWindow 
{
public:
    RootWindow(const char * title, int posX, int posY, int width, int height);
    ~RootWindow();
    void Init(); // must be called from the main GUI loop
    void ProcessEvent(SDL_Event ev);
    void Render();
    void AddWidget(std::shared_ptr<Widget> widget);
    unsigned int GetWindowID();
    
    bool initialized;
private:

    enum TraverseType
    {
        Drawing,
        EventProcessing,
        RendererRegistration
    };

    void TraverseWidgets(TraverseType ttype);


    std::shared_ptr<Widget> rootWidget;
    std::shared_ptr<SDLWindow> sdlWindow;
    std::shared_ptr<SDLRenderer> sdlRenderer;

    int widgetCount;
    SDL_Event currentEvent;
    bool visible;

    std::string windowTitle;
    int wPosX;
    int wPosY;
    int wWidth;
    int wHeight;
};

#endif // ROOTWINDOW_H
