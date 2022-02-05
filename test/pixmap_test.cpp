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

    constexpr int width = 1600;
    constexpr int height = 1000;
    std::shared_ptr<RootWindow> RW_Window1 = ge.CreateRootWindow("Pixmap test", 50, 50, width, height);
    std::shared_ptr<Pixmap> pixmap = std::make_shared<Pixmap>();
    pixmap->SetSize(width, height);
    RW_Window1->AddWidget(pixmap);
    ge.AddWindow(RW_Window1);
    std::thread controlThread([&]()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<int> distW(0, width);
        std::uniform_int_distribution<int> distH(0, height);
        std::uniform_int_distribution<unsigned char> distC(0, 255);
        for(int tick = 0 ; tick < 100000; ++tick)
        {
            int x = distW(gen);
            int y = distH(gen);
            SDL_Color c = {distC(gen), distC(gen), distC(gen), SDL_ALPHA_OPAQUE};
//            std::cout << "Tick: " << tick << " x: " << x << " y:" << y << std::endl;
            pixmap->PutPixel(x, y, c);
            //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        pixmap->saveToPNG("pixmap.png");
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

