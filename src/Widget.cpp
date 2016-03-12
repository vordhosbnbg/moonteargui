#include "Widget.h"
using namespace std;


Widget::Widget() : cached(false)
{
    srcRect.SetX(0);
    srcRect.SetY(0);
    srcRect.SetW(0);
    srcRect.SetH(0);
    dstRect.SetX(0);
    dstRect.SetY(0);
    dstRect.SetW(0);
    dstRect.SetH(0);
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
    dstRect.SetX(x);
}

void Widget::SetY(int y)
{
    lock_guard<mutex> lock(mxWidget);
    dstRect.SetY(y);
}

void Widget::SetW(int w)
{
    lock_guard<mutex> lock(mxWidget);
    dstRect.SetW(w);
}

void Widget::SetH(int h)
{
    lock_guard<mutex> lock(mxWidget);
    dstRect.SetH(h);
}

int Widget::GetX()
{
    return dstRect.GetX();
}

int Widget::GetY()
{
    return dstRect.GetY();
}

int Widget::GetW()
{
    return dstRect.GetW();
}

int Widget::GetH()
{
    return dstRect.GetH();
}

void Widget::Draw()
{
}
