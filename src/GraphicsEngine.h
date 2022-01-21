#pragma once

#include <memory>
#include <list>
#include <atomic>
#include <thread>
#include "Widget.h"
#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "RootWindow.h"
#include "AnimationManager.h"


class GraphicsEngine 
{
public:
    GraphicsEngine();
    ~GraphicsEngine();

    std::shared_ptr<RootWindow> CreateRootWindow(const char * title, int posX, int posY, int width, int height);
    void AddWindow(std::shared_ptr<RootWindow> wnd);

    void AddAnimation(std::shared_ptr<IAnimation> anim);
    void Start();
    void MainLoop();
    void Stop();
private:
    void InitIfNecessary();
    std::atomic<bool> isRunning{false};
    std::shared_ptr<std::thread> mainThread;
    std::shared_ptr<std::thread> inputThread;
    std::list<std::shared_ptr<RootWindow>> windowListActive;
    std::list<std::shared_ptr<RootWindow>> windowListToInit;
    std::shared_ptr<Widget> widgetTreeRoot;
    std::shared_ptr<AnimationManager> animationManager;
};

