#include "WidgetBuilder.h"
#include "BitmapResource.h"
#include "Image.h"

WidgetBuilder::WidgetBuilder(SDLRenderer & rnd) : renderer(&rnd)
{
}

WidgetBuilder::~WidgetBuilder()
{
}

std::shared_ptr<Widget> WidgetBuilder::BuildWidget(std::string& widgetType, std::shared_ptr<ResourcePack>& resourcePack)
{
    std::shared_ptr<Widget> retVal = nullptr;

    if (widgetType == "Image")
    {
        std::shared_ptr<BitmapResource> bitmapRes = std::static_pointer_cast<BitmapResource>(resourcePack->GetResource(ResID::Bitmap));
        if (bitmapRes) 
        {
            retVal = std::make_shared<Image>(bitmapRes);
        }
    }
    else if (widgetType == "Text")
    {

    }


    return retVal;
}
