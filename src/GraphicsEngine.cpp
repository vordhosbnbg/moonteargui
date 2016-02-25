#include "GraphicsEngine.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
using namespace std;


GraphicsEngine::GraphicsEngine()
{
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    TTF_Init();
}

GraphicsEngine::~GraphicsEngine()
{
    Stop();
    mainThread->join();
}


void GraphicsEngine::AddWindow(shared_ptr<RootWindow> wnd)
{
    windowList.push_back(wnd);
}

void GraphicsEngine::Start()
{
    isRunning.test_and_set();
    mainThread = make_shared<thread>(&GraphicsEngine::MainLoop, this);
}

void GraphicsEngine::MainLoop()
{
    while (isRunning.test_and_set()) 
    {
        for (auto iterWnd = windowList.begin(); iterWnd != windowList.end(); ++iterWnd) 
        {
            (*iterWnd)->Render();
        }
    }
}

void GraphicsEngine::Stop()
{
    isRunning.clear();
}
