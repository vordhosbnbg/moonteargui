#include <iostream>

#include "Widget.h"
#include "utils.h"


Widget::Widget() :
    widgetPosX(0),
    widgetPosY(0),
    widgetWidth(0),
    widgetHeight(0),
    rotationAngle(0),
    cached(false),
    focused(false)
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

void Widget::ProcessEvent(const SDL_Event& ev)
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
    DBGPRINT("Widget SetX - " << x << std::endl);
    widgetPosX = x;
}

void Widget::SetY(int y)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    DBGPRINT("Widget SetY - " << y << std::endl);
    widgetPosY = y;
}

void Widget::SetW(int w)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    DBGPRINT("Widget SetW - " << w << std::endl);
    widgetWidth = w;
}

void Widget::SetH(int h)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    DBGPRINT("Widget SetH - " << h << std::endl);
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

void Widget::SetRotation(int degree)
{
    rotationAngle = degree;
}

int Widget::GetRotation()
{
    return rotationAngle;
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
