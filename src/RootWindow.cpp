#include <stack>
#include "RootWindow.h"
using namespace std;

RootWindow::RootWindow(shared_ptr<SDLWindow> window) : sdlWindow(window), widgetCount(0)
{
    sdlRenderer = make_shared<SDLRenderer>(sdlWindow);
    rootWidget = make_shared<Widget>();
}

RootWindow::~RootWindow()
{
}

void RootWindow::Render()
{
    sdlRenderer->Clear();
    TraverseWidgets();
    sdlRenderer->RenderPresent();
}

void RootWindow::AddWidget(shared_ptr<Widget> widget)
{
    rootWidget->AttachChild(widget);
    widget->RegisterRenderer(sdlRenderer);
    widgetCount++;
}

void RootWindow::TraverseWidgets()
{
    stack<shared_ptr<Widget>> stackOfWidgets;
    auto iter = rootWidget;
    auto iterChild = iter->GetFirstChild();
    auto iterSibling = iter->GetFirstChild();
    while (iter)
    {
        iter->Draw(); // draw each tree node
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

