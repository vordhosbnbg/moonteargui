#include "GraphicsEngine.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
using namespace std;


GraphicsEngine::GraphicsEngine()
{
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    TTF_Init();
}

GraphicsEngine::~GraphicsEngine()
{
    Stop();
    mainThread->join();
}

shared_ptr<RootWindow> GraphicsEngine::CreateRootWindow(const char * title, int posX, int posY, int width, int height)
{
    return make_shared<RootWindow>(title, posX, posY, width, height);
}

void GraphicsEngine::AddWindow(shared_ptr<RootWindow> wnd)
{
    windowListToInit.push_back(wnd);
}


void GraphicsEngine::Start()
{
    isRunning.test_and_set();
    mainThread = make_shared<thread>(&GraphicsEngine::MainLoop, this);
}

void GraphicsEngine::MainLoop()
{
    SDL_Event ev;
    while (isRunning.test_and_set())
    {
        InitIfNecessary();
        for (auto iterWnd = windowListActive.begin(); iterWnd != windowListActive.end(); ++iterWnd)
        {
            while(SDL_PollEvent(&ev))
            {
                switch (ev.type)
                {
                case SDL_QUIT:
                    Stop();
                    break;
                case SDL_WINDOWEVENT:
                    if (ev.window.windowID == (*iterWnd)->GetWindowID())
                    {
                        (*iterWnd)->ProcessEvent(ev);
                    }
                    break;
                default:
                    (*iterWnd)->ProcessEvent(ev);
                    break;
                }
            }
            (*iterWnd)->Render();
        }
    }
}


void GraphicsEngine::Stop()
{
    isRunning.clear();
}

void GraphicsEngine::InitIfNecessary()
{
    if (windowListToInit.size() > 0)
    {
        auto iterWnd = windowListToInit.begin();
        while (iterWnd != windowListToInit.end())
        {
            (*iterWnd)->Init();
            windowListActive.push_back(*iterWnd);
            iterWnd = windowListToInit.erase(iterWnd);
        }
    }
}
