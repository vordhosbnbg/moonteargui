#include <Windows.h>
#include "SDL_main.h"
#include "pugixml.hpp"
#include "GraphicsEngine.h"
#include "main.h"
#include "BitmapResource.h"
#include "Image.h"
#include "TextResource.h"
#include "Text.h"
#include "FontResource.h"

using namespace std;

int main(int argc, char *argv[]) 
{
    GraphicsEngine ge;


    shared_ptr<SDLWindow> SDLW_Window1 = make_shared<SDLWindow>("Saphire GUI", 50, 50, 1024, 768);
    shared_ptr<RootWindow> RW_Window1 = make_shared<RootWindow>(SDLW_Window1);
    shared_ptr<BitmapResource> Res_lack_of_tests = make_shared<BitmapResource>(".\\res\\img\\lack_of_tests.jpg");
    shared_ptr<BitmapResource> Res_trippy_colors = make_shared<BitmapResource>(".\\res\\img\\trippy-colors.png");
    shared_ptr<TextResource> Res_TestText01 = make_shared<TextResource>(".\\res\\txt\\TestText01.xml");
    shared_ptr<FontResource> Res_Hack_Regular = make_shared<FontResource>(".\\res\\ttf\\Hack-Regular.ttf", 34);
    Res_lack_of_tests->Load();
    Res_trippy_colors->Load();
    Res_TestText01->Load();
    Res_Hack_Regular->Load();
    shared_ptr<Image> ImageWidget1 = make_shared<Image>(Res_lack_of_tests);
    shared_ptr<Image> ImageWidget2 = make_shared<Image>(Res_trippy_colors);
    shared_ptr<Text> TextWidet1 = make_shared<Text>(Res_TestText01, Res_Hack_Regular);
    ImageWidget1->SetX(20);
    ImageWidget1->SetY(300);
    ImageWidget2->SetX(500);
    ImageWidget2->SetY(20);
    TextWidet1->SetX(400);
    TextWidet1->SetY(400);
    RW_Window1->AddWidget(ImageWidget1);
    RW_Window1->AddWidget(ImageWidget2);
    RW_Window1->AddWidget(TextWidet1);
    ge.AddWindow(RW_Window1);
    ge.Start();

    Sleep(5000);
    ge.Stop();

    return 0;
}

