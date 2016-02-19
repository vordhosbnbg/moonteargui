#ifndef WIDGETBUILDER_H
#define WIDGETBUILDER_H

#include <string>
#include "Widget.h"
#include "ResourcePack.h"


class WidgetBuilder 
{
public:
    WidgetBuilder(SDLRenderer & rnd);
    ~WidgetBuilder();

    shared_ptr<Widget> BuildWidget(string widgetType, shared_ptr<ResourcePack> resourcePack);

    SDLRenderer * renderer;
};

#endif // WIDGETBUILDER_H
