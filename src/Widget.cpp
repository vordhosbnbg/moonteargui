#include "Widget.h"



Widget::Widget() : cached(false), focused(false), widgetPosX(0), widgetPosY(0), widgetWidth(0), widgetHeight(0)
{
}


Widget::~Widget()
{
}

void Widget::RegisterRenderer(std::shared_ptr<SDLRenderer> rend)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    sdlRenderer = rend;
    OnRegisterRenderer();
}

void Widget::OnRegisterRenderer()
{
}

void Widget::ProcessEvent(SDL_Event ev)
{
}

void Widget::AttachChild(std::shared_ptr<Widget> child)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    if (!firstChild)
    {
        firstChild = child;
    } 
    else
    {
        firstChild->AttachSibling(child);
    }
}

void Widget::AttachSibling(std::shared_ptr<Widget> sibling)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    if (!nextSibling)
    {
        nextSibling = sibling;
    }
    else 
    {
        auto iter = nextSibling;
        while (iter)
        {
            auto next = iter->GetNextSibling();
            if (!next) 
            {
                iter->nextSibling = sibling;
            }
            iter = next;
        }
        iter = sibling;
    }
}

std::shared_ptr<Widget> Widget::GetFirstChild()
{
    std::lock_guard<std::mutex> lock(mxWidget);
    return firstChild;
}

std::shared_ptr<Widget> Widget::GetNextSibling()
{
    std::lock_guard<std::mutex> lock(mxWidget);
    return nextSibling;
}

void Widget::SetX(int x)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    widgetPosX = x;
}

void Widget::SetY(int y)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    widgetPosY = y;
}

void Widget::SetW(int w)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    widgetWidth = w;
}

void Widget::SetH(int h)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    widgetHeight = h;
}

int Widget::GetX()
{
    return widgetPosX;
}

int Widget::GetY()
{
    return widgetPosY;
}

int Widget::GetW()
{
    return widgetWidth;
}

int Widget::GetH()
{
    return widgetHeight;
}

void Widget::SetFocused(bool val)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    focused = val;
}

bool Widget::IsFocused()
{
    std::lock_guard<std::mutex> lock(mxWidget);
    return focused;
}

void Widget::Draw()
{
}
