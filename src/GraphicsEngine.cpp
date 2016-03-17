#include "GraphicsEngine.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
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
    SDL_Event ev;
    while (isRunning.test_and_set())
    {
        for (auto iterWnd = windowList.begin(); iterWnd != windowList.end(); ++iterWnd) 
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
