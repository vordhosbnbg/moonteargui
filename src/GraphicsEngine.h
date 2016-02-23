#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H
#include <memory>
#include <vector>
#include <atomic>
#include <thread>
#include "Widget.h"
#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "RootWindow.h"

class GraphicsEngine 
{
public:
    GraphicsEngine();
    ~GraphicsEngine();

    void AddWindow(std::shared_ptr<RootWindow> wnd);
    void Start();
    void MainLoop();
    void Stop();
private:
    std::atomic_flag isRunning;
    std::shared_ptr<std::thread> mainThread;
    std::vector<std::shared_ptr<RootWindow>> windowList;
    std::shared_ptr<Widget> widgetTreeRoot;
};

#endif //GRAPHICSENGINE_H
