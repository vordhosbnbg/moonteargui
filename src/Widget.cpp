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

Widget::Widget(const Widget &other) :
    widgetPosX(other.widgetPosX),
    widgetPosY(other.widgetPosY),
    widgetWidth(other.widgetWidth),
    widgetHeight(other.widgetHeight),
    rotationAngle(other.rotationAngle),
    cached(other.cached),
    focused(other.focused)
{
}

Widget::Widget(const Widget&& other) noexcept :
    widgetPosX(other.widgetPosX),
    widgetPosY(other.widgetPosY),
    widgetWidth(other.widgetWidth),
    widgetHeight(other.widgetHeight),
    rotationAngle(other.rotationAngle),
    cached(other.cached),
    focused(other.focused)
{
}

Widget& Widget::operator=(const Widget& other)
{
    widgetPosX = other.widgetPosX;
    widgetPosY = other.widgetPosY;
    widgetWidth = other.widgetWidth;
    widgetHeight = other.widgetHeight;
    rotationAngle = other.rotationAngle;
    cached = other.cached;
    focused = other.focused;
    return *this;
}

Widget& Widget::operator=(Widget&& other) noexcept
{
    widgetPosX = other.widgetPosX;
    widgetPosY = other.widgetPosY;
    widgetWidth = other.widgetWidth;
    widgetHeight = other.widgetHeight;
    rotationAngle = other.rotationAngle;
    cached = other.cached;
    focused = other.focused;
    return *this;
}




void Widget::RegisterRenderer(const std::shared_ptr<SDLRenderer>& rend)
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

void Widget::AttachChild(const std::shared_ptr<Widget>& child)
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

void Widget::AttachSibling(const std::shared_ptr<Widget>& sibling)
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
