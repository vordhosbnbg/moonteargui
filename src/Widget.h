#pragma once

#include <mutex>
#include "SDLRenderer.h"
#include "utils.h"

class Widget
{
public:
    Widget();
    Widget(const Widget& other);
    Widget(const Widget&& other) noexcept;
    Widget& operator=(const Widget& other);
    Widget& operator=(Widget&& other) noexcept;

    virtual ~Widget() = default;

    void RegisterRenderer(const std::shared_ptr<SDLRenderer>& rend);
    void AttachChild(const std::shared_ptr<Widget>& child);
    void AttachSibling(const std::shared_ptr<Widget>& sibling);
    std::shared_ptr<Widget> GetFirstChild();
    std::shared_ptr<Widget> GetNextSibling();

    void SetX(float x)
    {
        std::lock_guard<std::mutex> lock(mxWidget);
        DBGPRINT("Widget SetX - " << x << std::endl);
        widgetPosX = x;
    }
    void SetY(float y)
    {
        std::lock_guard<std::mutex> lock(mxWidget);
        DBGPRINT("Widget SetY - " << y << std::endl);
        widgetPosY = y;
    }
    void SetW(float w)
    {
        std::lock_guard<std::mutex> lock(mxWidget);
        DBGPRINT("Widget SetW - " << w << std::endl);
        widgetWidth = w;
    }
    void SetH(float h)
    {
        std::lock_guard<std::mutex> lock(mxWidget);
        DBGPRINT("Widget SetH - " << h << std::endl);
        widgetHeight = h;
    }
    float GetX()
    {
        return widgetPosX;
    }
    float GetY()
    {
        return widgetPosY;
    }
    float GetW()
    {
        return widgetWidth;
    }
    float GetH()
    {
        return widgetHeight;
    }

    void SetRotation(int degree)
    {
        std::lock_guard<std::mutex> lock(mxWidget);
        rotationAngle = degree;
    }
    double GetRotation()
    {
        return rotationAngle;
    }

    void SetFocused(bool val);
    bool IsFocused();

    virtual void Draw();
    virtual void ProcessEvent(const SDL_Event& ev);


protected:
    virtual void OnRegisterRenderer();
    float widgetPosX;
    float widgetPosY;
    float widgetWidth;
    float widgetHeight;
    double rotationAngle;
    std::shared_ptr<SDLRenderer> sdlRenderer;
    bool cached;
    bool focused;
    std::mutex mxWidget;

private:
    std::shared_ptr<Widget> firstChild;
    std::shared_ptr<Widget> nextSibling;
};

