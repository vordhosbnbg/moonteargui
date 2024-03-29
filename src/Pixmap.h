#pragma once
#include <vector>
#include <iostream>
#include "Widget.h"

class Pixmap : public Widget
{
public:
    Pixmap() = default;



    void SetSize(int w, int h)
    {
        pixmapWidth = w;
        pixmapHeight = h;
        SetW(w);
        SetH(h);
        resizeBuffer();
    }

    inline bool PutPixel(unsigned int x, unsigned int y, SDL_Color col)
    {
        if(y*pixmapWidth + x < pointBuffer.size())
        {
//            std::cout << "PutPixel: " << y*pixmapWidth + x << std::endl;
            pointBuffer[y*pixmapWidth + x] = col;
            cached = false;
        }

        return false;
    }

    void saveToPNG(const char* filename);

    void Draw() override;
    void ProcessEvent(const SDL_Event& ev) override;

private:
    void resizeBuffer();
    void RenderPixmapToTexture();

    int pixmapWidth{0};
    int pixmapHeight{0};

    SDL_Color bgColor{0,0,0,255};
    std::vector<SDL_Color> pointBuffer;

    SDLRect srcRect;
    SDLFRect dstRect;

    std::shared_ptr<SDLTexture> pixmapTexture;

};
