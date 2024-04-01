#include <iostream>
#include <SDL2/SDL.h>
#include <chrono>
#include <thread>
#include <vector>

const int WIDTH = 800, HEIGHT = 800;

void drawFilledRect(SDL_Renderer *renderer, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}

void drawState(SDL_Renderer *renderer, std::vector<int> v, int ind1, int ind2)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (i == ind1)
        {
            drawFilledRect(renderer, i * (WIDTH / v.size()), HEIGHT - v[i], WIDTH / v.size(), v[i], 0, 0, 255);
        }
        else if (i == ind2)
        {
            drawFilledRect(renderer, i * (WIDTH / v.size()), HEIGHT - v[i], WIDTH / v.size(), v[i], 255, 0, 0);
        }
        else
        {
            drawFilledRect(renderer, i * (WIDTH / v.size()), HEIGHT - v[i], WIDTH / v.size(), v[i], 255, 255, 255);
        }
    }
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("AlgoVision", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == nullptr)
    {
        std::cout << "An error has occured: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cout << "An error has occured: " << SDL_GetError() << "\n";
        return -1;
    }

    std::vector<int> v = {500, 400, 100, 200, 150, 200, 300, 700, 800, 150, 175, 374};
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = i; j < v.size(); j++)
        {
            if (v[j] < v[i])
            {
                std::swap(v[i], v[j]);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);

            drawState(renderer, v, i, j);

            SDL_RenderPresent(renderer);
            SDL_Delay(100);
        }
    }

    SDL_Event windowEvent;
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
            {
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}