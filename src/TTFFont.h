#ifndef TTFFONT_H
#define TTFFONT_H
#include <memory>
#include <string>
#include "SDL_ttf.h"

struct TTF_Font_deleter
{
    void operator()(TTF_Font *p) const { TTF_CloseFont(p); }
};



class TTFFont 
{
public:
    TTFFont(std::string filename, int sizePt);
    ~TTFFont();

    TTF_Font * GetRawHandle();
protected:
    std::unique_ptr<TTF_Font, TTF_Font_deleter> font_handle;
};

#endif // TTFFONT_H
