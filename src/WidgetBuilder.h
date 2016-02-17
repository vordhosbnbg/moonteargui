#ifndef WIDGETBUILDER_H
#define WIDGETBUILDER_H

#include <string>
#include "Widget.h"


class WidgetBuilder 
{
public:
    WidgetBuilder();
    ~WidgetBuilder();

    shared_ptr<Widget> BuildWidget(string widgetType);
};

#endif // WIDGETBUILDER_H
