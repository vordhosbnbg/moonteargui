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

using namespace std;
class GraphicsEngine 
{
public:
    GraphicsEngine();
    ~GraphicsEngine();

    void AddWindow(shared_ptr<RootWindow> wnd);
    void Start();
    void MainLoop();
    void Stop();
private:
    atomic_flag isRunning;
    shared_ptr<thread> mainThread;
    vector<shared_ptr<RootWindow>> windowList;
    shared_ptr<Widget> widgetTreeRoot;
};

#endif //GRAPHICSENGINE_H
