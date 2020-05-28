#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <SDL.h>

const int WIDTHSCREEN = 1000;
const int HEIGHTSCREEN = 800;

const int HOLDERWIDTH = 80;
const int HOLDERHEIGHT = 80;


const char* TITLE = "WINDOW";
class Holder
{
private:
    int xpos;
    int ypos;
    SDL_Texture* holderImage;
    int width;
    int height;
public:
    Holder(SDL_Renderer* renderer)
    {
        SDL_Surface* surfaceTemp = SDL_LoadBMP("holder.bmp");
        SDL_SetColorKey(surfaceTemp,-1,SDL_MapRGB(surfaceTemp->format,0,255,255));
        this->holderImage = SDL_CreateTextureFromSurface(renderer,surfaceTemp);
        this->ypos = (HEIGHTSCREEN-HOLDERHEIGHT);
        this->xpos = (WIDTHSCREEN-HOLDERWIDTH)/2;
        this->width = HOLDERWIDTH;
        this->height = HOLDERHEIGHT;
        SDL_FreeSurface(surfaceTemp);
    }
    ~Holder()
    {
        SDL_DestroyTexture(holderImage);
    }
    void handleMove()
    {
        int mx, my;
        Uint8 mstate = SDL_GetMouseState(&mx, &my);
        if (mx < HOLDERWIDTH/2) xpos = 0;
        else if (mx > (WIDTHSCREEN - HOLDERWIDTH/2)) xpos = WIDTHSCREEN-HOLDERWIDTH;
        else xpos = mx - HOLDERWIDTH/2;
    }
    void render(SDL_Renderer* renderer)
    {
        SDL_Rect rect;
        rect.x = int(this->xpos+0.5f);
        rect.y = this->ypos;
        rect.w = this->width;
        rect.h = this->height;

        SDL_RenderCopy(renderer,holderImage,NULL,&rect);
    }
    int getYpos()
    {
        return ypos;
    }

    int getHeight()
    {
        return height;
    }
    int getXpos()
    {
        return xpos;
    }
    int getWidth()
    {
        return width;
    }

};

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
#endif // CORE_H_INCLUDED
