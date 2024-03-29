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

    std::shared_ptr<RootWindow> RW_Window1 = ge.CreateRootWindow("Moontear GUI", 50, 50, 1024, 768);
    std::shared_ptr<BitmapResource> Res_lack_of_tests = std::make_shared<BitmapResource>("./res/img/lack_of_tests.jpg");
    std::shared_ptr<BitmapResource> Res_trippy_colors = std::make_shared<BitmapResource>("./res/img/trippy-colors.png");
    std::shared_ptr<TextResource> Res_TestText01 = std::make_shared<TextResource>("./res/txt/TestText01.xml");
    std::shared_ptr<FontResource> Res_Hack_Regular = std::make_shared<FontResource>("./res/ttf/Hack-Regular.ttf", 34);
    Res_lack_of_tests->Load();
    Res_trippy_colors->Load();
    Res_TestText01->Load();
    Res_Hack_Regular->Load();
    std::shared_ptr<Image> ImageWidget1 = std::make_shared<Image>(Res_lack_of_tests);
    std::shared_ptr<Image> ImageWidget2 = std::make_shared<Image>(Res_trippy_colors);
    std::shared_ptr<Text> TextWidet1 = std::make_shared<Text>(Res_TestText01, Res_Hack_Regular);
    ImageWidget1->SetX(20);
    ImageWidget1->SetY(300);
    ImageWidget2->SetX(500);
    ImageWidget2->SetY(20);
    TextWidet1->SetX(400);
    TextWidet1->SetY(400);
    TextWidet1->SetW(200);
    TextWidet1->SetH(100);
    TextWidet1->SetBGColor({ 0x0F,0x0F,0x0F,0xFF });
    TextWidet1->SetFGColor({ 0xAF,0xAF,0x0B,0x80 });
    RW_Window1->AddWidget(ImageWidget1);
    RW_Window1->AddWidget(ImageWidget2);
    RW_Window1->AddWidget(TextWidet1);
    ge.AddWindow(RW_Window1);
    std::thread controlThread([&]()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        ImageWidget1->SetX(50);
        ImageWidget1->SetY(220);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        ImageWidget2->SetX(400);
        ImageWidget2->SetY(100);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        TextWidet1->SetX(10);
        TextWidet1->SetY(10);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        TextWidet1->SetBGColor({ 0xFF,0xFF,0xFF,0x80 });
        TextWidet1->SetFGColor({ 0x1F,0x60,0x00,0x00 });
        TextWidet1->SetFocused(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(20000));
        ge.Stop();
    });
    ge.Start();
    controlThread.join();
}

int main(int argc, char *argv[]) 
{
    Test();
    return 0;
}

