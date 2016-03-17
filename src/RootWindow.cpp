#include <stack>
#include "RootWindow.h"
using namespace std;

RootWindow::RootWindow(shared_ptr<SDLWindow> window) : sdlWindow(window), widgetCount(0), visible(true)
{
    sdlRenderer = make_shared<SDLRenderer>(sdlWindow);
    rootWidget = make_shared<Widget>();
    SDL_StartTextInput();
}

RootWindow::~RootWindow()
{
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

void RootWindow::AddWidget(shared_ptr<Widget> widget)
{
    rootWidget->AttachChild(widget);
    widget->RegisterRenderer(sdlRenderer);
    widgetCount++;
}

unsigned int RootWindow::GetWindowID()
{
    return sdlWindow->windowID;
}

void RootWindow::TraverseWidgets(TraverseType ttype)
{
    stack<shared_ptr<Widget>> stackOfWidgets;
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

