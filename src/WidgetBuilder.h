#ifndef WIDGETBUILDER_H
#define WIDGETBUILDER_H

#include <string>
#include <memory>
#include "Widget.h"
#include "ResourcePack.h"


class WidgetBuilder 
{
public:
    WidgetBuilder(SDLRenderer & rnd);
    ~WidgetBuilder();

    std::shared_ptr<Widget> BuildWidget(std::string widgetType, std::shared_ptr<ResourcePack> resourcePack);

    SDLRenderer * renderer;
};

#endif // WIDGETBUILDER_H
