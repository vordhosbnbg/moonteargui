#include <signal.h>
#include "SDL2/SDL_main.h"
#include "pugixml.hpp"
#include "GraphicsEngine.h"
#include "BitmapResource.h"
#include "Image.h"
#include "TextResource.h"
#include "Text.h"
#include "FontResource.h"



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

    std::shared_ptr<RootWindow> RW_Window1 = ge.CreateRootWindow("Image benchmark - position and resource change", 50, 50, 1600, 900);
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

    std::shared_ptr<Image> ImageWidget1 = std::make_shared<Image>(Res_Mercury);
    std::shared_ptr<Image> ImageWidget2 = std::make_shared<Image>(Res_Venus);
    std::shared_ptr<Image> ImageWidget3 = std::make_shared<Image>(Res_Earth);
    std::shared_ptr<Text> TextWidet1 = std::make_shared<Text>(nullptr, Res_Hack_Regular);
    TextWidet1->SetBGColor({0x00,0x00,0x00,0xFF});
    TextWidet1->SetFGColor({0xFF,0xFF,0xFF,0xFF});
    TextWidet1->SetX(100);
    TextWidet1->SetY(100);

    ImageWidget1->SetX(100);
    ImageWidget1->SetY(100);
    ImageWidget2->SetX(500);
    ImageWidget2->SetY(100);
    ImageWidget3->SetX(900);
    ImageWidget3->SetY(100);
    RW_Window1->AddWidget(ImageWidget1);
    RW_Window1->AddWidget(ImageWidget2);
    RW_Window1->AddWidget(ImageWidget3);
    ge.AddWindow(RW_Window1);
    ge.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));


    // w1: 100 --> 500
    // w2: 100 --> 50
    // w3: 100 --> 300
    int w1yStart = 100;
    int w1yEnd = 500;
    int w2yStart = 100;
    int w2yEnd = 50;
    int w3yStart = 100;
    int w3yEnd = 300;

    constexpr int durationSeconds = 10;
    constexpr int fps = 60;
    constexpr int totalFrames = durationSeconds * fps;
    for (int frames = 0; frames < totalFrames; ++frames)
    {
        int w1y = w1yStart + ((w1yEnd - w1yStart) * frames) / totalFrames;
        int w2y = w1yStart + ((w2yEnd - w2yStart) * frames) / totalFrames;
        int w3y = w1yStart + ((w3yEnd - w3yStart) * frames) / totalFrames;
        ImageWidget1->SetY(w1y);
        ImageWidget2->SetY(w2y);
        ImageWidget3->SetY(w3y);
        if(frames*100/totalFrames == 40)
        {
            ImageWidget1->SetBitmap(Res_Venus);
            ImageWidget2->SetBitmap(Res_Earth);
            ImageWidget3->SetBitmap(Res_Mars);
        }
        else if(frames*100/totalFrames == 60)
        {
            ImageWidget1->SetBitmap(Res_Earth);
            ImageWidget2->SetBitmap(Res_Mars);
            ImageWidget3->SetBitmap(Res_Jupiter);
        }
        else if(frames*100/totalFrames == 70)
        {
            ImageWidget1->SetBitmap(Res_Earth);
            ImageWidget2->SetBitmap(Res_Mars);
            ImageWidget3->SetBitmap(Res_Jupiter);
        }
        else if(frames*100/totalFrames == 80)
        {
            ImageWidget1->SetBitmap(Res_Mars);
            ImageWidget2->SetBitmap(Res_Jupiter);
            ImageWidget3->SetBitmap(Res_Uranus);
        }
        else if(frames*100/totalFrames == 90)
        {
            ImageWidget1->SetBitmap(Res_Jupiter);
            ImageWidget2->SetBitmap(Res_Uranus);
            ImageWidget3->SetBitmap(Res_Neptune);
        }
        else if(frames*100/totalFrames == 95)
        {
            ImageWidget1->SetBitmap(Res_Uranus);
            ImageWidget2->SetBitmap(Res_Neptune);
            ImageWidget3->SetBitmap(Res_Pluto);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/fps));
    }

    ge.Stop();
}

int main(int argc, char *argv[])
{
    Test();
    return 0;
}

