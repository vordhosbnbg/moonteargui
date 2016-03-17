#include "Widget.h"
using namespace std;


Widget::Widget() : cached(false), focused(false), widgetPosX(0), widgetPosY(0), widgetWidth(0), widgetHeight(0)
{
}


Widget::~Widget()
{
}

void Widget::RegisterRenderer(shared_ptr<SDLRenderer> rend)
{
    lock_guard<mutex> lock(mxWidget);
    sdlRenderer = rend;
    OnRegisterRenderer();
}

void Widget::OnRegisterRenderer()
{
}

void Widget::ProcessEvent(SDL_Event ev)
{
}

void Widget::AttachChild(shared_ptr<Widget> child)
{
    lock_guard<mutex> lock(mxWidget);
    if (!firstChild)
    {
        firstChild = child;
    } 
    else
    {
        firstChild->AttachSibling(child);
    }
}

void Widget::AttachSibling(shared_ptr<Widget> sibling)
{
    lock_guard<mutex> lock(mxWidget);
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

shared_ptr<Widget> Widget::GetFirstChild()
{
    lock_guard<mutex> lock(mxWidget);
    return firstChild;
}

shared_ptr<Widget> Widget::GetNextSibling()
{
    lock_guard<mutex> lock(mxWidget);
    return nextSibling;
}

void Widget::SetX(int x)
{
    lock_guard<mutex> lock(mxWidget);
    widgetPosX = x;
}

void Widget::SetY(int y)
{
    lock_guard<mutex> lock(mxWidget);
    widgetPosY = y;
}

void Widget::SetW(int w)
{
    lock_guard<mutex> lock(mxWidget);
    widgetWidth = w;
}

void Widget::SetH(int h)
{
    lock_guard<mutex> lock(mxWidget);
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
    lock_guard<mutex> lock(mxWidget);
    focused = val;
}

bool Widget::IsFocused()
{
    lock_guard<mutex> lock(mxWidget);
    return focused;
}

void Widget::Draw()
{
}
