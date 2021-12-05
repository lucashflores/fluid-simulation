#include "Graphics.h"


Graphics::Graphics (int width, int height): width(width), height(height) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

Graphics::~Graphics () {
    renderer = nullptr;
    window = nullptr;
}

void Graphics::drawPixel (int x, int y, float d) {
    SDL_SetRenderDrawColor(renderer, 255 * d, 255 * d, 255 * d, 255);
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_RenderPresent(renderer);
}

void Graphics::update () {
    if(SDL_PollEvent(&event) && event.type == SDL_QUIT) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(0);
    }
}