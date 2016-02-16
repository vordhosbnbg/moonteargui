#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H
#include <memory>
#include "SDL.h"
#include "SdlDeleter.h"

using namespace std;
class SDLTexture
{
public:
    SDLTexture();
    ~SDLTexture();

private:
    unique_ptr<SDL_Texture, sdl_deleter> texture_handle;
};
#endif //SDLTEXTURE_H
