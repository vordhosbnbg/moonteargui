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

void Widget::RegisterRenderer(SDLRenderer * rend)
{
    sdlRenderer = rend;
    OnRegisterRenderer();
}

void Widget::OnRegisterRenderer()
{
}

void Widget::AttachChild(shared_ptr<Widget> child)
{
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
    return firstChild;
}

shared_ptr<Widget> Widget::GetNextSibling()
{
    return nextSibling;
}

void Widget::SetX(int x)
{
    dstRect.SetX(x);
}

void Widget::SetY(int y)
{
    dstRect.SetY(y);
}

void Widget::SetW(int w)
{
    dstRect.SetW(w);
}

void Widget::SetH(int h)
{
    dstRect.SetH(h);
}

void Widget::Draw()
{
}
