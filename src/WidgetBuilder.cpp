#include "WidgetBuilder.h"
#include "BitmapResource.h"
#include "Image.h"

WidgetBuilder::WidgetBuilder(SDLRenderer & rnd) : renderer(&rnd)
{
}

WidgetBuilder::~WidgetBuilder()
{
}

shared_ptr<Widget> WidgetBuilder::BuildWidget(string widgetType, shared_ptr<ResourcePack> resourcePack)
{
    shared_ptr<Widget> retVal = nullptr;

    if (widgetType.compare("Image")) 
    {
        shared_ptr<BitmapResource> bitmapRes = static_pointer_cast<BitmapResource>(resourcePack->GetResource(ResID::Bitmap));
        if (bitmapRes) 
        {
            retVal = make_shared<Image>(bitmapRes, renderer);
        }
    }
    else if (widgetType.compare("Text"))
    {

    }


    return retVal;
}
