#ifndef BROAD_H_INCLUDED
#define BROAD_H_INCLUDED

#include <SDL.h>
#include "core.h"
#include <vector>
#include "Dropobj.h"
#include "math.h"

class Board
{
private:
    SDL_Texture* backGround;
    Holder* holder;
    vector <DropObj*> dropList;
    int life;
    int score;
public:
    Board(SDL_Renderer* renderer)
    {
        score = 0;
        life = 4;
        holder = new Holder(renderer);
        SDL_Surface* surfaceTemp =SDL_LoadBMP("background.bmp");
        this->backGround = SDL_CreateTextureFromSurface(renderer,surfaceTemp);
        SDL_FreeSurface(surfaceTemp);
    }

    void newDrop(SDL_Renderer* renderer)
    {
       static int i = 0;
       i++;
       if (i<1000) return;
       i = 0;
       dropList.push_back(new DropObj(renderer));
    }

    void Update(float delta,SDL_Renderer* renderer)
    {
        newDrop(renderer);
        for (int i=0;i<dropList.size();i++)
        {
            dropList[i]->handleMove(delta);
        }
        for (int i=0;i<dropList.size();i++)
        {
            if (((dropList[i]->getYpos() > (HEIGHTSCREEN-dropList[i]->getHeight() ) ) ))
            {
                int type = dropList[i]->getType();
                cout << "TYPE OF OBJ THAT JUST DROPPED : " << type << endl;

                delete dropList[i];
                dropList.erase(dropList.begin()+i);
                life--;
            }
        }
        holder->handleMove();
        for (int i=0;i<dropList.size();i++)
        {
            collisionCheck(dropList[i],i);
        }
    }

    bool isLost()
    {
        return (life < 1);
    }

    int getLife()
    {
        return life;
    }

    void collisionCheck(DropObj* obj,int i)
    {
        int xObj = obj->getXpos();
        int yObj = obj->getYpos();
        int wObj = obj->getWidth();
        int hObj = obj->getHeight();
        int x = holder->getXpos();
        int y = holder->getYpos();
        int w = holder->getWidth();
        int h = holder->getHeight();

        int xCenter1 = xObj + wObj/2;
        int yCenter1 = yObj + hObj/2;
        int xCenter2 = x + w/2;
        int yCenter2 = y + h/2;

        if ((abs(xCenter1-xCenter2) < (wObj/2 + w/2)) && (abs(yCenter1-yCenter2) < (hObj/2 + h/2)))
        {

            if (yObj + hObj/2 < HEIGHTSCREEN-75)
            {
                int type = dropList[i]->getType();
                if (type == SHIT) life--;
                else if (type == GoldenEGG) score += 30;
                else if (type == EGG) score += 10;
                else if (type == RottenEGG) score -= 10;
            }


            dropList.erase(dropList.begin()+i);
            delete obj;

        }
    }

    int getScore()
    {
        return score;
    }
    void render(SDL_Renderer* renderer)
    {
        SDL_Rect fullRect;
        fullRect.x = 0;
        fullRect.y = 0;
        fullRect.w = WIDTHSCREEN;
        fullRect.h = HEIGHTSCREEN;

        SDL_RenderCopy(renderer,backGround,NULL,&fullRect);
        holder->render(renderer);
        for (int i=0;i<dropList.size();i++)
        {
            dropList[i]->render(renderer);
        }
    }
};

#endif // BROAD_H_INCLUDED
