#include <stack>
#include "RootWindow.h"



RootWindow::RootWindow(const char * title, int posX, int posY, int width, int height) : widgetCount(0), visible(true), initialized(false), wPosX(posX), wPosY(posY), wWidth(width), wHeight(height)
{
    rootWidget = std::make_shared<Widget>();
}

RootWindow::~RootWindow()
{
}

void RootWindow::Init()
{
    if (!initialized)
    {
        sdlWindow = std::make_shared<SDLWindow>(windowTitle.c_str(), wPosX, wPosY, wWidth, wHeight);
        sdlRenderer = std::make_shared<SDLRenderer>(sdlWindow);
        TraverseWidgets(RendererRegistration);
        initialized = true;
    }
}

void RootWindow::ProcessEvent(SDL_Event ev)
{
    currentEvent = ev;
    if (ev.type == SDL_WINDOWEVENT)
    {
        switch (ev.window.event)
        {
        case SDL_WINDOWEVENT_ENTER:
            break;
        case SDL_WINDOWEVENT_LEAVE:
            break;
        case SDL_WINDOWEVENT_CLOSE:
            sdlWindow->Hide();
            break;
        }
    }
    TraverseWidgets(EventProcessing);
}

void RootWindow::Render()
{
    if (visible)
    {
        sdlRenderer->Clear();
        TraverseWidgets(Drawing);
        sdlRenderer->RenderPresent();
    }
}

void RootWindow::AddWidget(std::shared_ptr<Widget> widget)
{
    rootWidget->AttachChild(widget);
    if (sdlRenderer)
    {
        widget->RegisterRenderer(sdlRenderer);
    }
    widgetCount++;
}

unsigned int RootWindow::GetWindowID()
{
    return sdlWindow->windowID;
}

void RootWindow::TraverseWidgets(TraverseType ttype)
{
    std::stack<std::shared_ptr<Widget>> stackOfWidgets;
    auto iter = rootWidget;
    auto iterChild = iter->GetFirstChild();
    auto iterSibling = iter->GetFirstChild();
    while (iter)
    {
        // process each tree node
        switch (ttype)
        {
        case RootWindow::Drawing:
            iter->Draw();
            break;
        case RootWindow::EventProcessing:
            iter->ProcessEvent(currentEvent);
            break;
        case RootWindow::RendererRegistration:
            iter->RegisterRenderer(sdlRenderer);
            break;
        default:
            break;
        }
        iterChild = iter->GetFirstChild();
        if (iterChild)
        {
            iterSibling = iter->GetNextSibling();
            if (iterSibling) 
            {
                stackOfWidgets.push(iterSibling); // if there is a sibling we save it for later
            }
            iter = iterChild; // if there is a child we traverse down
        }
        else 
        {
            iterSibling = iter->GetNextSibling();
            if (!iterSibling) 
            {
                if (!stackOfWidgets.empty())
                {
                    iterSibling = stackOfWidgets.top(); // if we have saved nodes lets try to get them
                    stackOfWidgets.pop();
                }
            }

            iter = iterSibling; // if there is no child we either go either to the next sibling, next or become empty
        }
    }
}

