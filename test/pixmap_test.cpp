#include <random>
#include <signal.h>
#include "GraphicsEngine.h"
#include "Pixmap.h"



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

    std::shared_ptr<RootWindow> RW_Window1 = ge.CreateRootWindow("Pixmap test", 50, 50, 1000, 1000);
    std::shared_ptr<Pixmap> pixmap = std::make_shared<Pixmap>();
    constexpr int width = 1000;
    constexpr int height = 1000;
    pixmap->SetSize(width, height);
    RW_Window1->AddWidget(pixmap);
    ge.AddWindow(RW_Window1);
    std::thread controlThread([&]()
    {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<int> distW(0, width);
        std::uniform_int_distribution<int> distH(0, height);
        std::uniform_int_distribution<unsigned char> distC(0, 255);
        for(int tick = 0 ; tick < 100000000; ++tick)
        {
            pixmap->PutPixel(distW(gen), distH(gen), {distC(gen), distC(gen), distC(gen), 255});
            //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(6000));

        ge.Stop();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

    });
    ge.Start();
    controlThread.join();
}

int main()
{
    Test();
    return 0;
}

