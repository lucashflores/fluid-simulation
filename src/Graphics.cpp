#include "Graphics.h"


Graphics::Graphics (int width, int height, float scaleX, float scaleY): width(width), height(height), now(SDL_GetPerformanceCounter()), last(0), dt(0) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Navier-Stokes (Trabalho de Calculo 3)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderSetScale(renderer, scaleX, scaleY);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

Graphics::~Graphics () {
    renderer = nullptr;
    window = nullptr;
}

void Graphics::drawPixel (int x, int y, float d, float v) {
    SDL_SetRenderDrawColor(renderer, v, 255, 255, d);
    SDL_RenderDrawPoint(renderer, x, y);
}

void Graphics::update () {
    last = now;
    now = SDL_GetPerformanceCounter();
    dt = static_cast<float>((now - last) / static_cast<float>(SDL_GetPerformanceFrequency()) );

    SDL_RenderPresent(renderer);
}

void Graphics::clearScreen () {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

const float Graphics::getDeltaTime() const {
    return dt;
}

void Graphics::terminate() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}