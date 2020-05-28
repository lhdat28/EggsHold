#ifndef DROPOBJ_H_INCLUDED
#define DROPOBJ_H_INCLUDED
#include <SDL.h>
#include "core.h"
#include <vector>
#include "broad.h"
#include <stdlib.h>

using namespace std;

int randegg(int n)
{
    if (n == 0) return 89;
    if (n == 1) return 336;
    if (n == 2) return 592;
    if (n == 3) return 848;
}
int randshit(int n)
{
    if (n == 0) return 108;
    if (n == 1) return 352;
    if (n == 2) return 608;
    if (n == 3) return 860;
}

enum
{
    EGG,
    SHIT,
    GoldenEGG,
    RottenEGG,
    TOTAL
};

class DropObj
{
private:
    SDL_Texture* image;
    int xpos;
    int ypos;
    int width;
    int height;
    int type;
    float speed;
public:
    DropObj(SDL_Renderer* renderer)
    {
        speed = 500;
        ypos = 178;
        int type = rand()%TOTAL;
        cout << "WHAT JUST CREATED: " << type << endl;
        if (type == EGG)
        {
            width = 23;
            height = 28;
            int ps = rand() % 4 ;
            xpos = randegg(ps);
            SDL_Surface* temp = SDL_LoadBMP("egg1.bmp");
            SDL_SetColorKey(temp,-1,SDL_MapRGB(temp->format,0,255,255));
            this->image= SDL_CreateTextureFromSurface(renderer,temp);
            SDL_FreeSurface(temp);
        }
        if (type == GoldenEGG)
        {
            width = 23;
            height = 28;
            int ps = rand() % 4 ;
            xpos = randegg(ps);
            SDL_Surface* temp = SDL_LoadBMP("goldenegg.bmp");
            SDL_SetColorKey(temp,-1,SDL_MapRGB(temp->format,0,255,255));
            this->image= SDL_CreateTextureFromSurface(renderer,temp);
            SDL_FreeSurface(temp);

        }

        if (type == RottenEGG)
        {
            width = 24;
            height = 33;
            int ps = rand() % 4 ;
            xpos = randegg(ps);
            SDL_Surface* temp = SDL_LoadBMP("rottenegg.bmp");
            SDL_SetColorKey(temp,-1,SDL_MapRGB(temp->format,0,255,255));
            this->image= SDL_CreateTextureFromSurface(renderer,temp);
            SDL_FreeSurface(temp);

        }
        if (type == SHIT)
        {
            width = 10;
            height = 10;
            int ps = rand() % 4 ;
            xpos = randshit(ps);
            SDL_Surface* temp = SDL_LoadBMP("shit.bmp");
            SDL_SetColorKey(temp,-1,SDL_MapRGB(temp->format,0,255,255));
            this->image= SDL_CreateTextureFromSurface(renderer,temp);
            SDL_FreeSurface(temp);
        }
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
    int getType()
    {
        return this->type;
    }
    void render(SDL_Renderer* renderer)
    {
        SDL_Rect rect;
        rect.x = this->xpos;
        rect.y = int(this->ypos+0.5f);
        rect.w = this->width;
        rect.h = this->height;

        SDL_RenderCopy(renderer,image,NULL,&rect);
    }

    void handleMove(float delta)
    {
        ypos += delta*speed;
    }

    ~DropObj()
    {
        SDL_DestroyTexture(image);
    }

};

class Button
{
private:
     SDL_Texture* startbutton;
     SDL_Texture* exitbutton;
public:
    Button(SDL_Renderer* renderer)
    {
        SDL_Surface* surfaceTempstart =SDL_LoadBMP("start.bmp");
        SDL_SetColorKey(surfaceTempstart,-1,SDL_MapRGB(surfaceTempstart->format,0,255,255));
        this->startbutton = SDL_CreateTextureFromSurface(renderer,surfaceTempstart);
        SDL_FreeSurface(surfaceTempstart);
        SDL_Surface* surfaceTempexit =SDL_LoadBMP("exit.bmp");
        SDL_SetColorKey(surfaceTempexit,-1,SDL_MapRGB(surfaceTempexit->format,0,255,255));
        this->exitbutton = SDL_CreateTextureFromSurface(renderer,surfaceTempexit);
        SDL_FreeSurface(surfaceTempexit);
    }
    void renderstart(SDL_Renderer* renderer)
    {
        SDL_Rect startRect;
        startRect.x = 400;
        startRect.y = 300;
        startRect.w = 340;
        startRect.h = 155;

        SDL_RenderCopy(renderer,startbutton,NULL,&startRect);
    }
    void renderexit(SDL_Renderer* renderer)
    {
        SDL_Rect exitRect;
        exitRect.x = 400;
        exitRect.y = 480;
        exitRect.w = 390;
        exitRect.h = 160;

        SDL_RenderCopy(renderer,exitbutton,NULL,&exitRect);
    }


};

class StartPage
{
private :
    SDL_Texture* startpage;
public:
    StartPage(SDL_Renderer* renderer)
    {
        SDL_Surface* surfaceTemp =SDL_LoadBMP("startpage.bmp");
        this->startpage = SDL_CreateTextureFromSurface(renderer,surfaceTemp);
        SDL_FreeSurface(surfaceTemp);
    }
    void render(SDL_Renderer* renderer)
    {
        SDL_Rect fullRect;
        fullRect.x = 0;
        fullRect.y = 0;
        fullRect.w = WIDTHSCREEN;
        fullRect.h = HEIGHTSCREEN;
        SDL_RenderCopy(renderer,startpage,NULL,&fullRect);
    }

};

#endif // DROPOBJ_H_INCLUDED
