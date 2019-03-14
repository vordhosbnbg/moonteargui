#pragma once

#include <mutex>
#include "SDLRenderer.h"

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

    void SetX(int x);
    void SetY(int y);
    void SetW(int w);
    void SetH(int h);
    int GetX();
    int GetY();
    int GetW();
    int GetH();

    void SetRotation(int degree);
    int GetRotation();

    void SetFocused(bool val);
    bool IsFocused();

    virtual void Draw();
    virtual void ProcessEvent(const SDL_Event& ev);


protected:
    virtual void OnRegisterRenderer();
    int widgetPosX;
    int widgetPosY;
    int widgetWidth;
    int widgetHeight;
    int rotationAngle;
    std::shared_ptr<SDLRenderer> sdlRenderer;
    bool cached;
    bool focused;
    std::mutex mxWidget;

private:
    std::shared_ptr<Widget> firstChild;
    std::shared_ptr<Widget> nextSibling;
};

