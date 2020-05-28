#ifndef HOLDER_H_INCLUDED
#define HOLDER_H_INCLUDED

#include <SDL.h>
#include "core.h"

class Holder
{
private:
    int xpos;
    int ypos;
    SDL_Texture* holderImage;
    int width;
    int height;
public:
    Holder(SDL_Renderer* renderer);
    ~Holder();
    void handleMove();
    void render(SDL_Renderer* renderer);

};


#endif // HOLDER_H_INCLUDED
