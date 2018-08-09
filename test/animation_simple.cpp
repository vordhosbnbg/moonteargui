#include <signal.h>
#include "SDL2/SDL_main.h"
#include "pugixml.hpp"
#include "GraphicsEngine.h"
#include "BitmapResource.h"
#include "Image.h"
#include "TextResource.h"
#include "Text.h"
#include "FontResource.h"
#include "Animation.h"



void my_handler(int s)
{
    printf("Caught signal %d\n",s);
    exit(0);
}

void Test()
{
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, nullptr);
    GraphicsEngine ge;

    std::shared_ptr<RootWindow> RW_Window1 = ge.CreateRootWindow("Image benchmark - position and resource change", 50, 50, 1700, 900);
    std::shared_ptr<BitmapResource> Res_Mercury = std::make_shared<BitmapResource>("./res/img/planets/mercury.png");
    std::shared_ptr<BitmapResource> Res_Venus = std::make_shared<BitmapResource>("./res/img/planets/venus.png");
    std::shared_ptr<BitmapResource> Res_Earth = std::make_shared<BitmapResource>("./res/img/planets/earth.png");
    std::shared_ptr<BitmapResource> Res_Mars = std::make_shared<BitmapResource>("./res/img/planets/mars.png");
    std::shared_ptr<BitmapResource> Res_Jupiter = std::make_shared<BitmapResource>("./res/img/planets/jupiter.png");
    std::shared_ptr<BitmapResource> Res_Saturn = std::make_shared<BitmapResource>("./res/img/planets/saturn.png");
    std::shared_ptr<BitmapResource> Res_Uranus = std::make_shared<BitmapResource>("./res/img/planets/uranus.png");
    std::shared_ptr<BitmapResource> Res_Neptune = std::make_shared<BitmapResource>("./res/img/planets/neptune.png");
    std::shared_ptr<BitmapResource> Res_Pluto = std::make_shared<BitmapResource>("./res/img/planets/pluto.png");
    std::shared_ptr<FontResource> Res_Hack_Regular = std::make_shared<FontResource>("./res/ttf/Hack-Regular.ttf", 34);
    Res_Mercury->Load();
    Res_Venus->Load();
    Res_Earth->Load();
    Res_Mars->Load();
    Res_Jupiter->Load();
    Res_Saturn->Load();
    Res_Uranus->Load();
    Res_Neptune->Load();
    Res_Pluto->Load();
    Res_Hack_Regular->Load();

    std::shared_ptr<Image> imageMercury = std::make_shared<Image>(Res_Mercury);
    std::shared_ptr<Image> imageVenus = std::make_shared<Image>(Res_Venus);
    std::shared_ptr<Image> imageEarth = std::make_shared<Image>(Res_Earth);
    std::shared_ptr<Image> imageMars = std::make_shared<Image>(Res_Mars);
    std::shared_ptr<Text> textDescription = std::make_shared<Text>(nullptr, Res_Hack_Regular);
    textDescription->SetBGColor({0x00,0x00,0x00,0x00});
    textDescription->SetFGColor({0xFF,0xFF,0xFF,0xFF});
    textDescription->SetX(50);
    textDescription->SetY(50);
    textDescription->SetW(1700);
    textDescription->SetH(100);
    textDescription->SetSizePt(10);
    textDescription->SetText("Simple animation test - moving 4 objects on screen");

    imageMercury->SetX(100);
    imageMercury->SetY(100);
    imageVenus->SetX(500);
    imageVenus->SetY(100);
    imageEarth->SetX(900);
    imageEarth->SetY(100);
    imageMars->SetX(1300);
    imageMars->SetY(100);
    RW_Window1->AddWidget(imageMercury);
    RW_Window1->AddWidget(imageVenus);
    RW_Window1->AddWidget(imageEarth);
    RW_Window1->AddWidget(imageMars);
    RW_Window1->AddWidget(textDescription);
    ge.AddWindow(RW_Window1);
    ge.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    textDescription->SetText("Mercury animation started - Y from 100 to 200 for 2000 ms");
    ge.AddAnimation(std::make_shared<Animation<int, Image>>(*imageMercury, &Image::SetY, 100, 200, 2000));
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    textDescription->SetText("Venus animation started - X (500->100) for 5000 ms");
    ge.AddAnimation(std::make_shared<Animation<int, Image>>(*imageVenus, &Image::SetX, 500, 100, 5000));
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    textDescription->SetText("Mars two animation start - X (1300->500) and Y (100->300) for 2000 ms");
    ge.AddAnimation(std::make_shared<Animation<int, Image>>(*imageMars, &Image::SetX, 1300, 500, 2000));
    ge.AddAnimation(std::make_shared<Animation<int, Image>>(*imageMars, &Image::SetY, 100, 300, 2000));
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    textDescription->SetText("Earth, three animations, X (900->1300) and Y (100->300) and size from 100% to 0 for 2000 ms");

    int earthW = imageEarth->GetW();
    int earthH = imageEarth->GetH();
    ge.AddAnimation(std::make_shared<Animation<int, Image>>(*imageEarth, &Image::SetX, 900, 1300, 2000));
    ge.AddAnimation(std::make_shared<Animation<int, Image>>(*imageEarth, &Image::SetY, 900, 1300, 2000));
    ge.AddAnimation(std::make_shared<Animation<int, Image>>(*imageEarth, &Image::SetW, earthW, 0, 2000));
    ge.AddAnimation(std::make_shared<Animation<int, Image>>(*imageEarth, &Image::SetH, earthH, 0, 2000));

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    ge.Stop();
}

int main(int argc, char *argv[])
{
    Test();
    return 0;
}

