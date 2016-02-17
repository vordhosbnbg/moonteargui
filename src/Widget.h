#ifndef WIDGET_H
#define WIDGET_H
#include "SDLRenderer.h"

class Widget
{
public:
    Widget();
    ~Widget();

    virtual void vDraw();
};

#endif // WIDGET_H
