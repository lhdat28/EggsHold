#include <SDL.h>
#include <iostream>
#include "core.h"
#include "broad.h"
#include <time.h>


bool Init(SDL_Window* &window,SDL_Renderer* &renderer)
{
    window = SDL_CreateWindow(TITLE,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTHSCREEN,HEIGHTSCREEN,SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Load Window var is error! \n";
        return false;
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Load Renderer var is error! \n";
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    if (!Init(window,renderer)) return 0;

    SDL_Event e;
    bool isPlay = false;

    while (1)
    {
        if (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT) break;
        int mx, my;
        Uint8 mstate = SDL_GetMouseState(&mx, &my);

        if (e.type== SDL_MOUSEBUTTONDOWN)
            if (e.button.button = SDL_BUTTON_LEFT)
        {
            if (mx > 400 && mx < 740 && my > 300 && my < 455)
            {
                isPlay = true;
                break;
            }
            if (mx > 400 && mx < 790 && my > 480 && my < 640)
                break;
        }
        StartPage* startpage = new StartPage(renderer);
        startpage->render(renderer);
        Button * button = new Button(renderer);
        button->renderstart(renderer);
        button->renderexit(renderer);
        SDL_RenderPresent(renderer);
    }

    if (isPlay == false) return 0;

    Holder* holder = new Holder(renderer);
    Board* board = new Board(renderer);

    float lastTick = SDL_GetTicks();
    while (1)
    {
        //cout<< board->getLife() << endl;
        float nowTick = SDL_GetTicks();

        if (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT) break;
        if (board->isLost()) break;
        board->Update((nowTick-lastTick)/1000.0f,renderer);
        lastTick = nowTick;

        SDL_RenderClear(renderer);
        board->render(renderer);

        SDL_RenderPresent(renderer);
    }

    cout << "Your score: " << board->getScore();

    delete holder;
    delete board;

    SDL_Quit();
    return 0;

}

