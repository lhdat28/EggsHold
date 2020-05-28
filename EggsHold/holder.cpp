#include <SDL.h>
#include "holder.h"

Holder::Holder(SDL_Renderer* renderer)
{
    SDL_Surface* surfaceTemp = SDL_LoadBMP("holder.bmp");
    this->holderImage = SDL_CreateTextureFromSurface(renderer,surfaceTemp);
    this->ypos = (HEIGHTSCREEN-HOLDERHEIGHT);
    this->xpos = (WIDTHSCREEN-HOLDERWIDTH)/2;
    this->width = HOLDERWIDTH;
    this->height = HOLDERHEIGHT;
}

Holder::~Holder()
{
    SDL_DestroyTexture(holderImage);
}

void Holder::handleMove()
{
    int mx, my;
    Uint8 mstate = SDL_GetMouseState(&mx, &my);

    if (mx < HOLDERWIDTH/2) xpos = 0;
    else if (mx > (WIDTHSCREEN - HOLDERWIDTH/2)) xpos = WIDTHSCREEN-HOLDERWIDTH;
    else xpos = mx - HOLDERWIDTH/2;
}

void Holder::render(SDL_Renderer* renderer)
{
    SDL_Rect rect;
    rect.x = this->xpos;
    rect.y = this->ypos;
    rect.w = this->width;
    rect.h = this->height;

    SDL_RenderCopy(renderer,holderImage,NULL,&rect);
}
