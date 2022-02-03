#include <signal.h>
#include <memory>
#include "GraphicsEngine.h"
#include "Plot.h"

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

    std::shared_ptr<Plot> testPlot = std::make_shared<Plot>();
    testPlot->SetX(20);
    testPlot->SetY(20);
    testPlot->SetW(1000);
    testPlot->SetH(400);
    testPlot->AddSerieData("BTC/USD", 1, 10000);
    testPlot->AddSerieData("BTC/USD", 2, 9635);
    testPlot->AddSerieData("BTC/USD", 3, 8334);
    testPlot->AddSerieData("BTC/USD", 4, 7445);
    testPlot->AddSerieData("BTC/USD", 5, 7510);
    testPlot->AddSerieData("BTC/USD", 6, 8091);
    testPlot->AddSerieData("BTC/USD", 7, 8250);
    testPlot->AddSerieData("BTC/USD", 8, 6862);
    testPlot->AddSerieData("BTC/USD", 9, 8296);
    testPlot->AddSerieData("BTC/USD", 10, 10292);
    testPlot->AddSerieData("BTC/USD", 11, 11863);
    testPlot->AddSerieData("BTC/USD", 12, 12334);
    testPlot->getSeries("BTC/USD").SetXRange(1,12);
    testPlot->getSeries("BTC/USD").SetYRange(0,20000);
    testPlot->getSeries("BTC/USD").color = {230, 240, 120, 255};

    std::shared_ptr<RootWindow> RW_Window1 = ge.CreateRootWindow("Plot test", 50, 50, 1700, 900);
    ge.AddWindow(RW_Window1);
    RW_Window1->AddWidget(testPlot);
    std::thread controlThread([&]()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        testPlot->AddSerieData("BTC/USD", 13, 12296);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        testPlot->AddSerieData("BTC/USD", 14, 15292);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        testPlot->AddSerieData("BTC/USD", 15, 16863);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        testPlot->AddSerieData("BTC/USD", 16, 18334);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        testPlot->AddSerieData("BTC/USD", 17, 17334);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        testPlot->AddSerieData("BTC/USD", 18, 16334);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        testPlot->AddSerieData("BTC/USD", 19, 13334);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        testPlot->AddSerieData("BTC/USD", 20, 17334);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        testPlot->AddSerieData("BTC/USD", 21, 22334);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        testPlot->AddSerieData("BTC/USD", 22, 21334);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        testPlot->AddSerieData("BTC/USD", 23, 26334);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        testPlot->AddSerieData("BTC/USD", 24, 33334);
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
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

