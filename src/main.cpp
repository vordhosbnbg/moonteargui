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

void Test() 
{
    GraphicsEngine ge;

    shared_ptr<RootWindow> RW_Window1 = ge.CreateRootWindow("Saphire GUI", 50, 50, 1024, 768);
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
    TextWidet1->SetW(250);
    TextWidet1->SetH(100);
    TextWidet1->SetBGColor({ 0x0F,0x0F,0x0F,0xFF });
    TextWidet1->SetFGColor({ 0xAF,0xAF,0x0B,0x80 });
    RW_Window1->AddWidget(ImageWidget1);
    RW_Window1->AddWidget(ImageWidget2);
    RW_Window1->AddWidget(TextWidet1);
    ge.AddWindow(RW_Window1);
    ge.Start();
    Sleep(2000);
    ImageWidget1->SetX(50);
    ImageWidget1->SetY(220);
    Sleep(1000);
    ImageWidget2->SetX(400);
    ImageWidget2->SetY(100);
    Sleep(1000);
    TextWidet1->SetX(10);
    TextWidet1->SetY(10);
    Sleep(1000);
    TextWidet1->SetBGColor({ 0xFF,0xFF,0xFF,0x80 });
    TextWidet1->SetFGColor({ 0x00,0x00,0x00,0x00 });
    TextWidet1->SetFocused(true);
    Sleep(20000);
    ge.Stop();
}

int main(int argc, char *argv[]) 
{
    Test();
    return 0;
}

