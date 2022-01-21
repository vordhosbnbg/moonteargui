#include <signal.h>
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

    std::shared_ptr<Image> ImageWidget1 = std::make_shared<Image>(Res_Mercury);
    std::shared_ptr<Image> ImageWidget2 = std::make_shared<Image>(Res_Venus);
    std::shared_ptr<Image> ImageWidget3 = std::make_shared<Image>(Res_Earth);
    std::shared_ptr<Image> ImageWidget4 = std::make_shared<Image>(Res_Saturn);
    std::shared_ptr<Text> TextWidet1 = std::make_shared<Text>(nullptr, Res_Hack_Regular);
    TextWidet1->SetBGColor({0x00,0x00,0x00,0xFF});
    TextWidet1->SetFGColor({0xFF,0xFF,0xFF,0xFF});
    TextWidet1->SetX(100);
    TextWidet1->SetY(800);
    TextWidet1->SetW(900);
    TextWidet1->SetH(100);
    TextWidet1->SetText("Frame: 0");

    ImageWidget1->SetX(100);
    ImageWidget1->SetY(100);
    ImageWidget2->SetX(500);
    ImageWidget2->SetY(100);
    ImageWidget3->SetX(900);
    ImageWidget3->SetY(100);
    ImageWidget4->SetX(1600);
    ImageWidget4->SetY(300);
    RW_Window1->AddWidget(ImageWidget1);
    RW_Window1->AddWidget(ImageWidget2);
    RW_Window1->AddWidget(ImageWidget3);
    RW_Window1->AddWidget(ImageWidget4);
    RW_Window1->AddWidget(TextWidet1);
    ge.AddWindow(RW_Window1);
    std::thread controlThread([&]()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));


        // w1: 100 --> 500
        // w2: 100 --> 50
        // w3: 100 --> 300
        // w4x: 1600 --> 100
        int w1yStart = 100;
        int w1yEnd = 500;
        int w2yStart = 100;
        int w2yEnd = 50;
        int w3yStart = 100;
        int w3yEnd = 300;
        int w4xStart = 1600;
        int w4xEnd = 100;

        constexpr int durationSeconds = 10;
        constexpr int fps = 60;
        constexpr int totalFrames = durationSeconds * fps;
        for (int frame = 0; frame < totalFrames; ++frame)
        {
            int w1y = w1yStart + ((w1yEnd - w1yStart) * frame) / totalFrames;
            int w2y = w2yStart + ((w2yEnd - w2yStart) * frame) / totalFrames;
            int w3y = w3yStart + ((w3yEnd - w3yStart) * frame) / totalFrames;
            int w4x = w4xStart + ((w4xEnd - w4xStart) * frame) / totalFrames;
            ImageWidget1->SetY(w1y);
            ImageWidget2->SetY(w2y);
            ImageWidget3->SetY(w3y);
            ImageWidget4->SetX(w4x);
            if(frame*100/totalFrames == 40)
            {
                ImageWidget1->SetBitmap(Res_Venus);
                ImageWidget2->SetBitmap(Res_Earth);
                ImageWidget3->SetBitmap(Res_Mars);
            }
            else if(frame*100/totalFrames == 60)
            {
                ImageWidget1->SetBitmap(Res_Earth);
                ImageWidget2->SetBitmap(Res_Mars);
                ImageWidget3->SetBitmap(Res_Jupiter);
            }
            else if(frame*100/totalFrames == 70)
            {
                ImageWidget1->SetBitmap(Res_Earth);
                ImageWidget2->SetBitmap(Res_Mars);
                ImageWidget3->SetBitmap(Res_Jupiter);
            }
            else if(frame*100/totalFrames == 80)
            {
                ImageWidget1->SetBitmap(Res_Mars);
                ImageWidget2->SetBitmap(Res_Jupiter);
                ImageWidget3->SetBitmap(Res_Uranus);
            }
            else if(frame*100/totalFrames == 90)
            {
                ImageWidget1->SetBitmap(Res_Jupiter);
                ImageWidget2->SetBitmap(Res_Uranus);
                ImageWidget3->SetBitmap(Res_Neptune);
            }
            else if(frame*100/totalFrames == 95)
            {
                ImageWidget1->SetBitmap(Res_Uranus);
                ImageWidget2->SetBitmap(Res_Neptune);
                ImageWidget3->SetBitmap(Res_Pluto);
            }
            TextWidet1->SetText("Frame: " + std::to_string(frame));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000/fps));
        }

        ge.Stop();
    });
    ge.Start();
}

int main(int argc, char *argv[])
{
    Test();
    return 0;
}

