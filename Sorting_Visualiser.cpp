#include <SDL2/SDL.h>
#include <random>
#include <ranges>
#include <algorithm>
#include <iostream>
using namespace std;

void draw_state(vector<int> &v, SDL_Renderer *renderer, unsigned int red, unsigned int blue)
{
    unsigned int index = 0;
    for (int i : v)
    {
        if (index == red)
            SDL_RenderdrawColor(renderer, 255, 0, 0, 255);
        else if (index == blue)
            SDL_RenderdrawColor(renderer, 0, 0, 255, 255);
        else
            SDL_RenderdrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, index, 99, index, i);
        index += i;
    }
}

int main()
{
    random_device rd;
    uniform_int_distribution d(1, 99);
    vector<int> v;

    // populate our vector with random numbers
    for (int i = 0; i < 100; i++)
    {
        v.push_back(d(rd));
    }

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowRenderer(100 * 10, 100 * 10, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);

    // sort algorithm
    for (unsigned int i = 0; i < v.size(); i++)
    {
        for (unsigned int j = i; j < v.size(); j++)
        {
            if (v[j] < v[i])
            {
                swap(v[j], v[i]);
             }
            // Clear screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Draw the state of the sort
            draw_state(v, renderer, i, j);

            // Show to window
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
    }
    for (int i : v)
    {
        cout << i << " ";
    }
    if (ranges::is_sorted(v))
    {
        cout << "\nsorted\n";
    }

    return 0;
}